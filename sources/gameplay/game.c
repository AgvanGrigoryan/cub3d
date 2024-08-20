/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:17:56 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/20 15:27:05 by natamazy         ###   ########.fr       */
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
		|| texs->so.img == NULL || texs->we.img == NULL)
		return (pred("XPM_FILE_TO_IMG failed\n", BOLD, 2), -1);
	total_height = texs->ea.h + texs->no.h + texs->so.h + texs->we.h;
	total_width = texs->ea.w + texs->no.w + texs->so.w + texs->we.w;
	if ((total_height / TEXS_CNT) != texs->ea.h
		|| (total_width / TEXS_CNT != texs->ea.w))
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
	// add to states of doors and sprite textures
	if (check_texs_img(&game->texs) == -1)
		return (destroy_texs_imgs(game->mlx, &game->texs));
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
}

int	game_init(t_game_info *game, t_scene_info *sc_info)
{
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
	mlx_hook(game->win, 2, 0, movement, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop(game->mlx);
	return (0);
}
