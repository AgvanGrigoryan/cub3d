/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:53 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/21 01:29:12 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_view(int keycode, t_player *pl)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = pl->dirX;
	oldPlaneX = pl->planeX;
	if(keycode == RIGHT_ARROW_KEYCODE)
	{
		pl->dirX = pl->dirX * cos(-ROT_SPEED) - pl->dirY * sin(-ROT_SPEED);
		pl->dirY = oldDirX * sin(-ROT_SPEED) + pl->dirY * cos(-ROT_SPEED);
		pl->planeX = pl->planeX * cos(-ROT_SPEED) - pl->planeY * sin(-ROT_SPEED);
		pl->planeY = oldPlaneX * sin(-ROT_SPEED) + pl->planeY * cos(-ROT_SPEED);
	}
	else if (keycode == LEFT_ARROW_KEYCODE)
	{
		//both camera direction and camera plane must be rotated
		pl->dirX = pl->dirX * cos(ROT_SPEED) - pl->dirY * sin(ROT_SPEED);
		pl->dirY = oldDirX * sin(ROT_SPEED) + pl->dirY * cos(ROT_SPEED);
		pl->planeX = pl->planeX * cos(ROT_SPEED) - pl->planeY * sin(ROT_SPEED);
		pl->planeY = oldPlaneX * sin(ROT_SPEED) + pl->planeY * cos(ROT_SPEED);
	}
}

void	move_left(t_line *map, t_player *pl)
{
	double x;
	double y;

	x = pl->posX - pl->dirY * WALK_SPEED;
	y = pl->posY;
	if (map[(int)x].val[(int)y] != '1')
		pl->posX = x;
	x = pl->posX;
	y = pl->posY + pl->dirX * WALK_SPEED;
	if (map[(int)x].val[(int)y] != '1')
		pl->posY = y;
}

void	move_right(t_line *map, t_player *pl)
{
	double x;
	double y;

	x = pl->posX + pl->dirY * WALK_SPEED;
	y = pl->posY;
	if (map[(int)x].val[(int)y] != '1')
		pl->posX = x;
	x = pl->posX;
	y = pl->posY - pl->dirX * WALK_SPEED;
	if (map[(int)x].val[(int)y] != '1')
		pl->posY = y;
}

void	move_back(t_line *map, t_player *pl)
{
	double x;
	double y;

	x = pl->posX - pl->dirX * WALK_SPEED;
	y = pl->posY;
	if (map[(int)x].val[(int)y] != '1')
		pl->posX = x;
	x = pl->posX;
	y = pl->posY - pl->dirY * WALK_SPEED;
	if (map[(int)x].val[(int)y] != '1')
		pl->posY = y;
}

void	move_ahead(t_line *map, t_player *pl)
{
	double	x;
	double	y;

	x = pl->posX + pl->dirX * WALK_SPEED;
	y = pl->posY;
	if (map[(int)x].val[(int)y] != '1')
		pl->posX = x;
	x = pl->posX;
	y = pl->posY + pl->dirY * WALK_SPEED;
	if (map[(int)x].val[(int)y] != '1')
		pl->posY = y;
}
