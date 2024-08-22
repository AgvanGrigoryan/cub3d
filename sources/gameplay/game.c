/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:17:56 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/22 15:58:54 by aggrigor         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"
#include "mlx.h"

int	close_game(t_game_info *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	exit (0);
}

int	destroy_texs_imgs(void *mlx, t_texs *texs)
{
	if (texs->ea.img != NULL
		&& mlx_destroy_image(mlx, texs->ea.img) == -1)
		return (-1);
	if (texs->no.img != NULL
		&& mlx_destroy_image(mlx, texs->no.img) == -1)
		return (-1);
	if (texs->so.img != NULL
		&& mlx_destroy_image(mlx, texs->so.img) == -1)
		return (-1);
	if (texs->we.img != NULL
		&& mlx_destroy_image(mlx, texs->we.img) == -1)
		return (-1);
	// 
	return (0);
}

int	check_texs_img(t_texs *texs)
{
	int		total_width;
	int		total_height;

	if (texs->ea.img == NULL || texs->no.img == NULL
		|| texs->so.img == NULL || texs->we.img == NULL || texs->dopen.img == NULL || texs->dclose.img == NULL)
		return (pred("XPM_FILE_TO_IMG failed\n", BOLD, 2), -1);
	total_height = texs->ea.h + texs->no.h + texs->so.h + texs->we.h + texs->dopen.h + texs->dclose.h;
	total_width = texs->ea.w + texs->no.w + texs->so.w + texs->we.w + texs->dopen.w + texs->dclose.w;
	if ((total_height / TEXS_CNT) != texs->ea.h
		|| (total_width / TEXS_CNT) != texs->ea.w)
		return (pred("Texs sizes are different\n", BOLD, 2), -1);
	return (0);
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
	game->texs.dopen.img = mlx_xpm_file_to_image(game->mlx,
			get_value(sc_info->texs, "DO"),
			&game->texs.dopen.w, &game->texs.dopen.h);
	game->texs.dclose.img = mlx_xpm_file_to_image(game->mlx,
			get_value(sc_info->texs, "DC"),
			&game->texs.dclose.w, &game->texs.dclose.h);
	// add to states of doors and sprite textures
	if (check_texs_img(&game->texs) == -1)
		return (destroy_texs_imgs(game->mlx, &game->texs), -1);
	game->texs.ea.addr = mlx_get_data_addr(game->texs.ea.img, &game->texs.ea.bpp, &game->texs.ea.line_len, &game->texs.ea.endian);
	game->texs.no.addr = mlx_get_data_addr(game->texs.no.img, &game->texs.no.bpp, &game->texs.no.line_len, &game->texs.no.endian);
	game->texs.so.addr = mlx_get_data_addr(game->texs.so.img, &game->texs.so.bpp, &game->texs.so.line_len, &game->texs.so.endian);
	game->texs.we.addr = mlx_get_data_addr(game->texs.we.img, &game->texs.we.bpp, &game->texs.we.line_len, &game->texs.we.endian);
	game->texs.dopen.addr = mlx_get_data_addr(game->texs.dopen.img, &game->texs.dopen.bpp, &game->texs.dopen.line_len, &game->texs.dopen.endian);
	game->texs.dclose.addr = mlx_get_data_addr(game->texs.dclose.img, &game->texs.dclose.bpp, &game->texs.dclose.line_len, &game->texs.dclose.endian);
	return (0);
}

int	init_flr_clg_colors(t_game_info *game, t_scene_info *sc_info)
{
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
	map[(int)pl->posX].val[(int)pl->posY] = '0';
}

int	game_init(t_game_info *game, t_scene_info *sc_info)
{
	game->pl.can_run = 0;
	game->map_rad = 5.0;
	game->is_map_mini = 1;
	game->pl.walk_speed = 0.2;
	game->map = sc_info->map;
	if (init_textures_img(game, sc_info) == -1)
		return (-1);
	if (init_flr_clg_colors(game, sc_info) == -1)
		return (destroy_texs_imgs(game->mlx, &game->texs), -1);
	init_player_info(game->map, &game->pl);
	game->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (game->img.img == NULL)
		return (-1);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (game->img.addr == NULL)
		return (mlx_destroy_image(game->mlx, game->img.img),
				destroy_texs_imgs(game->mlx, &game->texs), -1); // or call function and do this and other cleaning actions in that function
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
	mlx_hook(game->win, 2, 0, key_hook, game);
	mlx_hook(game->win, 3, 0, key_down_hook, game);
	mlx_hook(game->win, 6, 0, mouse_move, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop(game->mlx);
	return (0);
}
