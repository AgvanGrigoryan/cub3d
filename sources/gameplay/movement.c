/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:53 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/20 20:50:32 by natamazy         ###   ########.fr       */
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
