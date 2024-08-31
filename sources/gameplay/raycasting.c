/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:52:18 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/31 12:09:20 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	draw_line(t_ipoint p1, t_ipoint p2, int color, t_img *img);
void	draw_square(t_img *img, t_ipoint xy, int size, int color);
void	draw_mini_map(t_game_info *game);
void	draw_player(t_game_info *game, double s_i, double s_j);

void	draw_clg_and_flr(t_game_info *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H / 2)
	{
		j = 0;
		while (j < WIN_W)
		{
			my_mlx_pixel_put(&game->img, j, i, game->texs.clg);
			j++;
		}
		i++;
	}
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			my_mlx_pixel_put(&game->img, j, i, game->texs.flr);
			j++;
		}
		i++;
	}
}

void	choose_color(t_game_info *game, t_line *map, t_ipoint ij, t_dpoint	s)
{
	t_ipoint	xy;

	xy.x = CELL_SZ * (ij.y - s.y);
	xy.y = CELL_SZ * (ij.x - s.x);
	if (map[ij.x].val[ij.y] == '1')
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 204, 255, 204));
	else if (map[ij.x].val[ij.y] == 'D')
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 100, 100, 255));
	else if (map[ij.x].val[ij.y] == 'C')
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 69, 169, 69));
	else if (map[ij.x].val[ij.y] == '0' || (map[ij.x].val[ij.y] == 'W'
			|| map[ij.x].val[ij.y] == 'N'
			|| map[ij.x].val[ij.y] == 'S' || map[ij.x].val[ij.y] == 'E'))
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 255, 255, 255));
	else if (map[ij.x].val[ij.y] == ' ')
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 33, 33, 33));
}

char	*get_texture(t_game_info *game, int hit, int side, t_dpoint ray_dir)
{
	if (hit == 2)
		return (game->texs.dopen.addr);
	if (hit == 3)
		return (game->texs.dclose.addr);
	if (side == 1 && ray_dir.y <= 0)
		return (game->texs.no.addr);
	if (side == 0 && ray_dir.x > 0)
		return (game->texs.so.addr);
	if (side == 0 && ray_dir.x <= 0)
		return (game->texs.ea.addr);
	return (game->texs.we.addr);
}

void	raycasting_1(t_game_info *game, t_ray *ray)
{
	ray->map_x = (int) game->pl.pos_x;
	ray->mapY = (int) game->pl.pos_y;
	ray->camera_x = 2 * ray->x / (double)WIN_W - 1;
	ray->ray_dir.x = game->pl.dir_x + game->pl.plane_x * ray->camera_x;
	ray->ray_dir.y = game->pl.dir_y + game->pl.plane_y * ray->camera_x;
	ray->deltaDistX = ternard(ray->ray_dir.x == 0, 1e30,
			fabs(1 / ray->ray_dir.x));
	ray->deltaDistY = ternard(ray->ray_dir.y == 0, 1e30,
			fabs(1 / ray->ray_dir.y));
}

void	raycasting_2(t_game_info *game, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->pl.pos_x - ray->map_x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->map_x + 1.0 - game->pl.pos_x) * ray->deltaDistX;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->pl.pos_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->pl.pos_y) * ray->deltaDistY;
	}
}

void	raycasting_3(t_game_info *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->map_x += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->map[ray->map_x].val[ray->mapY] == '1')
			ray->hit = 1;
		else if (game->map[ray->map_x].val[ray->mapY] == 'C')
			ray->hit = 2;
		else if (game->map[ray->map_x].val[ray->mapY] == 'D')
			ray->hit = 3;
	}
}
