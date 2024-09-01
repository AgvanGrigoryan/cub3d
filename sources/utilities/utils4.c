/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:06:31 by aggrigor          #+#    #+#             */
/*   Updated: 2024/09/01 14:56:48 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ternard(int condition, double yes, double no)
{
	if (condition == 1)
		return (yes);
	return (no);
}

void	set_player_dir(char pl_dir, t_player *pl)
{
	pl->plane_x = 0;
	pl->plane_y = 0;
	pl->dir_y = 0;
	pl->dir_x = 0;
	if (pl_dir == 'W')
	{
		pl->dir_y = -1.0;
		pl->plane_x = -0.66;
	}
	else if (pl_dir == 'E')
	{
		pl->dir_y = 1.0;
		pl->plane_x = 0.66;
	}
	else if (pl_dir == 'S')
	{
		pl->dir_x = 1.0;
		pl->plane_y = -0.66;
	}
	else if (pl_dir == 'N')
	{
		pl->dir_x = -1.0;
		pl->plane_y = 0.66;
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
				pl->pos_x = (double) i + 0.5;
				pl->pos_y = (double) j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	open_door(t_game_info *game)
{
	int		i;
	int		j;

	i = (int)(game->pl.pos_x + game->pl.dir_x);
	j = (int)(game->pl.pos_y + game->pl.dir_y);
	if (game->map[i].val[j] == 'D')
		game->map[i].val[j] = 'C';
	else if (game->map[i].val[j] == 'C')
		game->map[i].val[j] = 'D';
}

int	key_hook(int key, t_game_info *game)
{
	key_hook_1(key, game);
	key_hook_2(key, game);
	return (key);
}
