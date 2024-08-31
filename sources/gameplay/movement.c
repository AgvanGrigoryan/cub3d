/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:53 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/31 12:07:46 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_left(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	x = pl->pos_x - pl->dir_y * pl->walk_speed;
	y = pl->pos_y;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->pos_x = x;
	x = pl->pos_x;
	y = pl->pos_y + pl->dir_x * pl->walk_speed;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->pos_y = y;
}

void	move_right(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	x = pl->pos_x + pl->dir_y * pl->walk_speed;
	y = pl->pos_y;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->pos_x = x;
	x = pl->pos_x;
	y = pl->pos_y - pl->dir_x * pl->walk_speed;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->pos_y = y;
}

void	move_back(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	x = pl->pos_x - pl->dir_x * pl->walk_speed;
	y = pl->pos_y;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->pos_x = x;
	x = pl->pos_x;
	y = pl->pos_y - pl->dir_y * pl->walk_speed;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->pos_y = y;
}

void	move_ahead(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	if (pl->can_run == 0)
		pl->can_run = 1;
	x = pl->pos_x + pl->dir_x * pl->walk_speed;
	y = pl->pos_y;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->pos_x = x;
	x = pl->pos_x;
	y = pl->pos_y + pl->dir_y * pl->walk_speed;
	if (map[(int)x].val[(int)y] != '1' && map[(int)x].val[(int)y] != 'D')
		pl->pos_y = y;
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
