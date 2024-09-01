/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:47:07 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/01 14:56:36 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

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
	if (check_texs_img(&game->texs) == -1)
		return (destroy_texs_imgs(game->mlx, &game->texs), -1);
	if (get_textures_data(game))
		return (destroy_texs_imgs(game->mlx, &game->texs), -1);
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
	set_player_dir(map[(int)pl->pos_x].val[(int)pl->pos_y], pl);
	map[(int)pl->pos_x].val[(int)pl->pos_y] = '0';
}

int	game_init(t_game_info *game, t_scene_info *sc_info)
{
	game->pl.can_run = 0;
	game->map_rad = 5.0;
	game->is_map_mini = 1;
	game->pl.walk_speed = 0.2;
	game->map = sc_info->map;
	get_torch_textures(game);
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
			destroy_texs_imgs(game->mlx, &game->texs), -1);
	game->img.w = WIN_W;
	game->img.h = WIN_H;
	return (0);
}
