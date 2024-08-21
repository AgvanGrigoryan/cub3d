/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:01:11 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/21 21:28:13 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_down_hook(int keycode, t_game_info *game)
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