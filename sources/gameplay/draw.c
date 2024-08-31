/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:10:14 by natamazy          #+#    #+#             */
/*   Updated: 2024/08/31 12:27:17 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	draw_player(t_game_info *game, double s_i, double s_j)
{
	int			line_len;
	t_ipoint	p1;
	t_ipoint	p2;
	t_dpoint	l_dir;
	t_dpoint	r_dir;

	line_len = 30;
	p1.x = (CELL_SZ * game->pl.pos_y) - (s_j * CELL_SZ);
	p1.y = (CELL_SZ * game->pl.pos_x) - (s_i * CELL_SZ);
	draw_square(&game->img, (t_ipoint){p1.x - CELL_SZ / 4, p1.y - CELL_SZ / 4},
		CELL_SZ / 2, create_trgb(0, 102, 153, 153));
	p2.x = p1.x + (game->pl.dir_y * line_len);
	p2.y = p1.y + (game->pl.dir_x * line_len);
	draw_line(p1, p2, create_trgb(0, 255, 0, 0), &game->img);
	draw_player_helper(game, &l_dir, &r_dir);
	p2.x = p1.x + (l_dir.y * line_len);
	p2.y = p1.y + (l_dir.x * line_len);
	draw_line(p1, p2, create_trgb(0, 0, 102, 255), &game->img);
	p2.x = p1.x + (r_dir.y * line_len);
	p2.y = p1.y + (r_dir.x * line_len);
	draw_line(p1, p2, create_trgb(0, 0, 102, 255), &game->img);
	draw_line(p2, (t_ipoint){p1.x + (l_dir.y * line_len),
		p1.y + (l_dir.x * line_len)}, create_trgb(0, 0, 255, 0), &game->img);
}

int	draw_scene(t_game_info *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_clg_and_flr(game);
	raycasting(game);
	torch_anim(game);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	my_mlx_image_clear(&game->img);
	return (0);
}

void	draw_line(t_ipoint p1, t_ipoint p2, int color, t_img *img)
{
	t_ipoint	d;
	t_ipoint	s;
	t_ipoint	e;

	d.x = abs(p2.x - p1.x);
	d.y = abs(p2.y - p1.y);
	s.x = ternard(p1.x < p2.x, 1, -1);
	s.y = ternard(p1.y < p2.y, 1, -1);
	e.x = d.x - d.y;
	while (1)
	{
		my_mlx_pixel_put(img, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		process_line(&d, &s, &e, &p1);
	}
}

void	draw_square(t_img *img, t_ipoint xy, int size, int color)
{
	int	i;
	int	j;

	i = xy.x;
	j = xy.y;
	while (i < xy.x + size + 1)
	{
		j = xy.y;
		while (j < xy.y + size + 1)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_game_info *game)
{
	t_line		*map;
	t_ipoint	ij;
	t_dpoint	s;

	map = game->map;
	ij.x = 0.0;
	if (game->pl.pos_x - game->map_rad > 0)
		ij.x = game->pl.pos_x - game->map_rad;
	s.x = ij.x;
	ij.y = 0.0;
	if (game->pl.pos_y - game->map_rad > 0)
		ij.y = game->pl.pos_y - game->map_rad;
	s.y = ij.y;
	while (map[ij.x].val != NULL && ij.x < s.x + 2 * game->map_rad)
	{
		ij.y = s.y;
		while (ij.y < map[ij.x].len && map[ij.x].val[ij.y]
			!= '\0' && ij.y < s.y + 2 * game->map_rad)
		{
			choose_color(game, map, ij, s);
			ij.y++;
		}
		ij.x++;
	}
	draw_player(game, s.x, s.y);
}
