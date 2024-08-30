/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:53 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/30 16:48:41 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_view(int keycode, t_player *pl, double rot_angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pl->dirX;
	old_plane_x = pl->planeX;
	if (keycode == RIGHT_ARR)
	{
		pl->dirX = pl->dirX * cos(-rot_angle) - pl->dirY * sin(-rot_angle);
		pl->dirY = old_dir_x * sin(-rot_angle) + pl->dirY * cos(-rot_angle);
		pl->planeX = pl->planeX * cos(-rot_angle)
			- pl->planeY * sin(-rot_angle);
		pl->planeY = old_plane_x * sin(-rot_angle)
			+ pl->planeY * cos(-rot_angle);
	}
	else if (keycode == LEFT_ARR)
	{
		pl->dirX = pl->dirX * cos(rot_angle) - pl->dirY * sin(rot_angle);
		pl->dirY = old_dir_x * sin(rot_angle) + pl->dirY * cos(rot_angle);
		pl->planeX = pl->planeX * cos(rot_angle) - pl->planeY * sin(rot_angle);
		pl->planeY = old_plane_x * sin(rot_angle) + pl->planeY * cos(rot_angle);
	}
}

void	move_left(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	x = pl->posX - pl->dirY * pl->walk_speed;
	y = pl->posY;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->posX = x;
	x = pl->posX;
	y = pl->posY + pl->dirX * pl->walk_speed;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->posY = y;
}

void	move_right(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	x = pl->posX + pl->dirY * pl->walk_speed;
	y = pl->posY;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->posX = x;
	x = pl->posX;
	y = pl->posY - pl->dirX * pl->walk_speed;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->posY = y;
}

void	move_back(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	x = pl->posX - pl->dirX * pl->walk_speed;
	y = pl->posY;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->posX = x;
	x = pl->posX;
	y = pl->posY - pl->dirY * pl->walk_speed;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->posY = y;
}

void	move_ahead(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	if (pl->can_run == 0)
		pl->can_run = 1;
	x = pl->posX + pl->dirX * pl->walk_speed;
	y = pl->posY;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->posX = x;
	x = pl->posX;
	y = pl->posY + pl->dirY * pl->walk_speed;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->posY = y;
}

int	mouse_move(int x, int y, t_game_info *game)
{
	static int	prev_x;
	double		rot_angle;

	(void) y;
	rot_angle = (double)(abs(x - prev_x) * MOUSE_ROT_SPEED);
	if (x > prev_x)
		rotate_view(RIGHT_ARR, &game->pl, rot_angle);
	else if (x < prev_x)
		rotate_view(LEFT_ARR, &game->pl, rot_angle);
	prev_x = x;
	return (0);
}
