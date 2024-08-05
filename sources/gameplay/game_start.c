/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:17:56 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/05 21:18:33 by aggrigor         ###   ########.fr       */
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

int	game_init(t_game_info *game, t_scene_info *sc_info)
{
	game->map = sc_info->map;
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
	game->texs.clg = str_to_trgb(get_value(sc_info->texs, "C"));
	game->texs.flr = str_to_trgb(get_value(sc_info->texs, "F"));
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
	for (int i = 0; i < WIN_H / 2; i++)
		for (int j = 0; j < WIN_W; j++)
			my_mlx_pixel_put(&game->img, j, i, game->texs.clg);
	for (int i = WIN_H / 2; i < WIN_H; i++)
		for (int j = 0; j < WIN_W; j++)
			my_mlx_pixel_put(&game->img, j, i, game->texs.flr);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop(game->mlx);
	return (0);
}
