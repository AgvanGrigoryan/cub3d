/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:34:18 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/03 18:07:59 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	get_torch_textures(t_game_info *game)
{
	int	i;

	set_torch_textures(game);
	if (!game->torch[0].img || !game->torch[1].img
		|| !game->torch[2].img || !game->torch[3].img
		|| !game->torch[4].img || !game->torch[5].img
		|| !game->torch[6].img || !game->torch[7].img)
		return (destroy_torch_imgs(game->mlx, game->torch), -1);
	i = -1;
	while (++i < 8)
	{
		game->torch[i].addr = mlx_get_data_addr(game->torch[i].img,
				&game->torch[i].bpp, &game->torch[i].line_len,
				&game->torch[i].endian);
		if (!game->torch[i].addr)
			return (destroy_torch_imgs(game->mlx, game->torch), -1);
	}
	return (0);
}

void	draw_player_helper(t_game_info *game, t_dpoint *l_dir, t_dpoint *r_dir)
{
	l_dir->x = game->pl.dir_x * cos(0.66) - game->pl.dir_y * sin(0.66);
	l_dir->y = game->pl.dir_x * sin(0.66) + game->pl.dir_y * cos(0.66);
	r_dir->x = game->pl.dir_x * cos(-0.66) - game->pl.dir_y * sin(-0.66);
	r_dir->y = game->pl.dir_x * sin(-0.66) + game->pl.dir_y * cos(-0.66);
}

void	process_line(t_ipoint *d, t_ipoint *s, t_ipoint *e, t_ipoint *p1)
{
	e->y = 2 * e->x;
	if (e->y > -d->y)
	{
		e->x -= d->y;
		p1->x += s->x;
	}
	if (e->y < d->x)
	{
		e->x += d->x;
		p1->y += s->y;
	}
}
