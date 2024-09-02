/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:41:35 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/02 17:53:39 by aggrigor         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"
#include "mlx.h"

void	raycasting_3(t_game_info *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_x].val[ray->map_y] == '1')
			ray->hit = 1;
		else if (game->map[ray->map_x].val[ray->map_y] == 'C')
			ray->hit = 2;
		else if (game->map[ray->map_x].val[ray->map_y] == 'D')
			ray->hit = 3;
	}
}

void	raycasting_4(t_game_info *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
	if (ray->side == 0)
		ray->wall_x = game->pl.pos_y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		ray->wall_x = game->pl.pos_x + ray->perp_wall_dist * ray->ray_dir.x;
	ray->wall_x -= floor((ray->wall_x));
}

void	raycasting_5(t_game_info *game, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)game->texs.ea.w);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->tex_x = game->texs.ea.w - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		ray->tex_x = game->texs.ea.w - ray->tex_x - 1;
	ray->step = 1.0 * 64 / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_H / 2
			+ ray->line_height / 2) * ray->step;
	ray->y = ray->draw_start;
	while (++ray->y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (game->texs.ea.w - 1);
		ray->tex_pos += ray->step;
		ray->color = *(((unsigned int *)get_texture(game,
						ray->hit, ray->side, ray->ray_dir))
				+ (game->texs.ea.h * ray->tex_y + ray->tex_x));
		if (ray->side == 1)
			ray->color = (ray->color >> 1) & 8355711;
		my_mlx_pixel_put(&game->img, ray->x, ray->y, ray->color);
	}
}

void	raycasting(t_game_info *game)
{
	t_ray	ray;

	ray.x = 0;
	while (ray.x < WIN_W)
	{
		raycasting_1(game, &ray);
		raycasting_2(game, &ray);
		raycasting_3(game, &ray);
		raycasting_4(game, &ray);
		raycasting_5(game, &ray);
		ray.x++;
	}
}
