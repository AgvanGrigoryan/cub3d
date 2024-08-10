/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:17:56 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/10 13:48:03 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	close_game(t_game_info *info)
{
	mlx_clear_window(info->mlx, info->win);
	mlx_destroy_window(info->mlx, info->win);
	exit (0);
}

int	init_textures_img(t_game_info *game, t_scene_info *sc_info)
{
	game->texs.ea.img = mlx_xpm_file_to_image(game->mlx,
			get_value(sc_info->texs, "EA"),
			&game->texs.ea.w, &game->texs.ea.h);
	game->texs.no.img = mlx_xpm_file_to_image(game->mlx,
			get_value(sc_info->texs, "NO"),
			&game->texs.no.w, &game->texs.no.h);
	game->texs.so.img = mlx_xpm_file_to_image(game->mlx,
			get_value(sc_info->texs, "SO"),
			&game->texs.so.w, &game->texs.so.h);
	game->texs.we.img = mlx_xpm_file_to_image(game->mlx,
			get_value(sc_info->texs, "WE"),
			&game->texs.we.w, &game->texs.we.h);
	if (!game->texs.ea.img || !game->texs.no.img
		|| !game->texs.so.img || !game->texs.we.img)
		return (pred("XMP_FILE_TO_IMAGE FAILED", BOLD, 2), -1);
	game->texs.clg = str_to_trgb(get_value(sc_info->texs, "C"));
	game->texs.flr = str_to_trgb(get_value(sc_info->texs, "F"));
	if (game->texs.clg == -1 || game->texs.flr == -1)
		return (-1);
	return (0);
}

void	init_player_info(t_line *map, t_player *pl)
{
	set_player_pos(map, pl);
	set_player_dir(map[(int)pl->posX].val[(int)pl->posY], pl);
}

int	game_init(t_game_info *game, t_scene_info *sc_info)
{
	game->map = sc_info->map;
	if (init_textures_img(game, sc_info) == -1)
		return (-1);
	init_player_info(game->map, &game->pl);
	game->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (game->img.img == NULL)
		return (-1);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (game->img.addr == NULL)
		return (mlx_destroy_image(game->mlx, game->img.img), -1); // or call function and do this and other cleaning actions in that function
	return (0);
}

int	game_start(t_scene_info *sc_info)
{
	t_game_info	*game;

	game = malloc(sizeof(t_game_info));
	if (game == NULL)
		return (perror("GAME_START"), -1);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (-1);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "CUB3D");
	if (game->win == NULL)
		return (-1);
	if (game_init(game, sc_info) == -1)
		return (-1);
	mlx_loop_hook(game->mlx, draw_scene, game);
	mlx_hook(game->win, 2, 0, movement, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop(game->mlx);
	return (0);
}
