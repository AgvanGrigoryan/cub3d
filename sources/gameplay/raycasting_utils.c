/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:41:35 by natamazy          #+#    #+#             */
/*   Updated: 2024/08/31 12:05:37 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	draw_line(t_ipoint p1, t_ipoint p2, int color, t_img *img);
void	draw_square(t_img *img, t_ipoint xy, int size, int color);
void	draw_mini_map(t_game_info *game);
void	draw_player(t_game_info *game, double s_i, double s_j);

void	raycasting_4(t_game_info *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	ray->lineHeight = (int)(WIN_H / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + WIN_H / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + WIN_H / 2;
	if (ray->drawEnd >= WIN_H)
		ray->drawEnd = WIN_H - 1;
	if (ray->side == 0)
		ray->wallX = game->pl.pos_y + ray->perpWallDist * ray->ray_dir.y;
	else
		ray->wallX = game->pl.pos_x + ray->perpWallDist * ray->ray_dir.x;
	ray->wallX -= floor((ray->wallX));
}

void	raycasting_5(t_game_info *game, t_ray *ray)
{
	ray->texX = (int)(ray->wallX * (double)game->texs.ea.w);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->texX = game->texs.ea.w - ray->texX - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		ray->texX = game->texs.ea.w - ray->texX - 1;
	ray->step = 1.0 * 64 / ray->lineHeight;
	ray->texPos = (ray->drawStart - WIN_H / 2
			+ ray->lineHeight / 2) * ray->step;
	ray->y = ray->drawStart;
	while (++ray->y < ray->drawEnd)
	{
		ray->texY = (int)ray->texPos & (game->texs.ea.w - 1);
		ray->texPos += ray->step;
		ray->color = *(((unsigned int *)get_texture(game,
						ray->hit, ray->side, ray->ray_dir))
				+ (game->texs.ea.h * ray->texY + ray->texX));
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

void	process_line(t_ipoint *d, t_ipoint *s, t_ipoint *e, t_ipoint *p1)
{
	e->y = 2 * e->x;
	if (e->y > -d->y)
	{
		e->x -= d->y;
		p1->x += s->x;
	}
	if (e->y < d->x)
	{
		e->x += d->x;
		p1->y += s->y;
	}
}
