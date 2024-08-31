/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:01:11 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/31 12:25:02 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_image_clear(t_img *img)
{
	int	offset;

	offset = 0;
	while (offset < (WIN_H * img->line_len))
	{
		*(img->addr + offset) = 0x0;
		offset++;
	}
}

int	key_down_hook(int keycode, t_game_info *game)
{
	if (keycode == SHIFT_KEYCODE)
	{
		if (game->pl.can_run == 2)
			game->pl.walk_speed /= 2.0;
		game->pl.can_run = 0;
	}
	if (keycode == W_KEYCODE)
		game->pl.can_run = 0;
	return (0);
}

void	key_hook_1(int key, t_game_info *game)
{
	if (key == ESC_KEYCODE)
		close_game(game);
	if (key == LEFT_ARR || key == RIGHT_ARR)
		rotate_view(key, &game->pl, ROT_SPEED);
	if (key == W_KEYCODE)
		move_ahead(game->map, &game->pl);
	if (key == S_KEYCODE)
		move_back(game->map, &game->pl);
	if (key == A_KEYCODE)
		move_left(game->map, &game->pl);
	if (key == D_KEYCODE)
		move_right(game->map, &game->pl);
	if (key == E_KEYCODE)
		open_door(game);
}

void	key_hook_2(int key, t_game_info *game)
{
	if (key == SHIFT_KEYCODE && game->pl.can_run == 1)
	{
		game->pl.walk_speed *= 2.0;
		game->pl.can_run = 2;
	}
	if (key == M_KEYCODE)
	{
		game->map_rad = 5;
		if (game->is_map_mini)
			game->map_rad *= 1000;
		game->is_map_mini = !game->is_map_mini;
	}
}

void	rotate_view(int keycode, t_player *pl, double rot_angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pl->dir_x;
	old_plane_x = pl->plane_x;
	if (keycode == RIGHT_ARR)
	{
		pl->dir_x = pl->dir_x * cos(-rot_angle) - pl->dir_y * sin(-rot_angle);
		pl->dir_y = old_dir_x * sin(-rot_angle) + pl->dir_y * cos(-rot_angle);
		pl->plane_x = pl->plane_x * cos(-rot_angle)
			- pl->plane_y * sin(-rot_angle);
		pl->plane_y = old_plane_x * sin(-rot_angle)
			+ pl->plane_y * cos(-rot_angle);
	}
	else if (keycode == LEFT_ARR)
	{
		pl->dir_x = pl->dir_x * cos(rot_angle) - pl->dir_y * sin(rot_angle);
		pl->dir_y = old_dir_x * sin(rot_angle) + pl->dir_y * cos(rot_angle);
		pl->plane_x = pl->plane_x * cos(rot_angle)
			- pl->plane_y * sin(rot_angle);
		pl->plane_y = old_plane_x * sin(rot_angle)
			+ pl->plane_y * cos(rot_angle);
	}
}
