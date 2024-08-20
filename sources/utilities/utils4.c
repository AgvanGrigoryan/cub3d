/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:06:31 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/21 01:17:31 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ternar for double numbers
double	ternard(int condition, double yes, double no)
{
	if (condition == 1)
		return (yes);
	return (no);
}

void	set_player_dir(char pl_dir, t_player *pl)
{
	pl->planeX = 0;
	pl->planeY = 0;
	pl->dirY = 0;
	pl->dirX = 0;
	if (pl_dir == 'W')
	{
		pl->dirY = -1.0;
		pl->planeX = -0.66;
	}
	else if (pl_dir == 'E')
	{
		pl->dirY = 1.0;
		pl->planeX = 0.66;
	}
	else if (pl_dir == 'S')
	{
		pl->dirX = 1.0;
		pl->planeY = -0.66;
	}
	else if (pl_dir == 'N')
	{
		pl->dirX = -1.0;
		pl->planeY = 0.66;
	}
}

void	set_player_pos(t_line *map, t_player *pl)
{
	int		i;
	int		j;

	i = 0;
	while (map[i].val != NULL)
	{
		j = 0;
		while (map[i].val[j] != '\0')
		{
			if (map[i].val[j] == 'W' || map[i].val[j] == 'N'
				|| map[i].val[j] == 'S' || map[i].val[j] == 'E')
			{
				pl->posX = (double) i + 0.5;
				pl->posY = (double) j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	key_hook(int key, t_game_info *game)
{
	if (key == ESC_KEYCODE)
		close_game(game);
	if (key == LEFT_ARROW_KEYCODE
		|| key == RIGHT_ARROW_KEYCODE)
		rotate_view(key, &game->pl);
	if (key == W_KEYCODE)
	{
		move_ahead(game->map, &game->pl);
		// game->pl.posX += game->pl.dirX * WALK_SPEED;
		// game->pl.posY += game->pl.dirY * WALK_SPEED;
	}
	if (key == S_KEYCODE)
	{
		move_back(game->map, &game->pl);
		// game->pl.posX -= game->pl.dirX * WALK_SPEED;
		// game->pl.posY -= game->pl.dirY * WALK_SPEED;
	}
	if (key == A_KEYCODE)
	{
		move_left(game->map, &game->pl);
		// game->pl.posY += game->pl.dirX * WALK_SPEED;
		// game->pl.posX -= game->pl.dirY * WALK_SPEED;
	}
	if (key == D_KEYCODE)
	{
		move_right(game->map, &game->pl);
		// game->pl.posY -= game->pl.dirX * WALK_SPEED;
		// game->pl.posX += game->pl.dirY * WALK_SPEED;
	}
	return (key);
}

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
