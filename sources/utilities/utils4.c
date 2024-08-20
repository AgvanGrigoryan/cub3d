/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:06:31 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/11 21:38:31 by aggrigor         ###   ########.fr       */
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
		pl->dirX = -1;
		pl->planeX = -0.66;
	}
	else if (pl_dir == 'E')
	{
		pl->dirX = 1;
		pl->planeX = 0.90;
	}
	else if (pl_dir == 'S')
	{
		pl->dirY = -1;
		pl->planeY = -0.66;
	}
	else if (pl_dir == 'N')
	{
		pl->dirY = 1;
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
				pl->posX = (double) i;
				pl->posY = (double) j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	movement(int key, t_game_info *game)
{
	if (key == LEFT_ARROW_KEYCODE
		|| key == RIGHT_ARROW_KEYCODE)
		rotate_view(key, &game->pl);
	if (key == W_KEYCODE)
	{
		game->pl.posX += game->pl.dirY * WALK_SPEED;
		game->pl.posY += game->pl.dirX * WALK_SPEED;
	}
	if (key == S_KEYCODE)
	{
		game->pl.posX -= game->pl.dirY * WALK_SPEED;
		game->pl.posY -= game->pl.dirX * WALK_SPEED;
	}
	if (key == A_KEYCODE)
	{
		game->pl.posY += game->pl.dirY * WALK_SPEED;
		game->pl.posX -= game->pl.dirX * WALK_SPEED;
	}
	if (key == D_KEYCODE)
	{
		game->pl.posY -= game->pl.dirY * WALK_SPEED;
		game->pl.posX += game->pl.dirX * WALK_SPEED;
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
