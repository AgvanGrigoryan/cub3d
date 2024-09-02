/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:44:01 by aggrigor          #+#    #+#             */
/*   Updated: 2024/09/02 18:09:20 by aggrigor         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"
#include "mlx.h"

int	close_game(t_game_info *game)
{
	mlx_destroy_image(game->mlx, game->torch[0].img);
	mlx_destroy_image(game->mlx, game->torch[1].img);
	mlx_destroy_image(game->mlx, game->torch[2].img);
	mlx_destroy_image(game->mlx, game->torch[3].img);
	mlx_destroy_image(game->mlx, game->torch[4].img);
	mlx_destroy_image(game->mlx, game->torch[5].img);
	mlx_destroy_image(game->mlx, game->torch[6].img);
	mlx_destroy_image(game->mlx, game->torch[7].img);
	mlx_destroy_image(game->mlx, game->texs.ea.img);
	mlx_destroy_image(game->mlx, game->texs.so.img);
	mlx_destroy_image(game->mlx, game->texs.no.img);
	mlx_destroy_image(game->mlx, game->texs.we.img);
	mlx_destroy_image(game->mlx, game->texs.dclose.img);
	mlx_destroy_image(game->mlx, game->texs.dopen.img);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	// system("leaks cub3D");
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
	if (texs->dopen.img != NULL
		&& mlx_destroy_image(mlx, texs->dopen.img) == -1)
		return (-1);
	if (texs->dclose.img != NULL
		&& mlx_destroy_image(mlx, texs->dclose.img) == -1)
		return (-1);
	return (0);
}

int	check_texs_img(t_texs *texs)
{
	int		total_width;
	int		total_height;

	if (texs->ea.img == NULL || texs->no.img == NULL
		|| texs->so.img == NULL || texs->we.img == NULL
		|| texs->dopen.img == NULL || texs->dclose.img == NULL)
		return (pred("XPM_FILE_TO_IMG failed\n", BOLD, 2), -1);
	total_height = texs->ea.h + texs->no.h + texs->so.h
		+ texs->we.h + texs->dopen.h + texs->dclose.h;
	total_width = texs->ea.w + texs->no.w + texs->so.w
		+ texs->we.w + texs->dopen.w + texs->dclose.w;
	if ((total_height / TEXS_CNT) != texs->ea.h
		|| (total_width / TEXS_CNT) != texs->ea.w)
		return (pred("Texs sizes are different\n", BOLD, 2), -1);
	return (0);
}

int	get_textures_data(t_game_info *game)
{
	game->texs.ea.addr = mlx_get_data_addr(game->texs.ea.img,
			&game->texs.ea.bpp, &game->texs.ea.line_len, &game->texs.ea.endian);
	game->texs.no.addr = mlx_get_data_addr(game->texs.no.img,
			&game->texs.no.bpp, &game->texs.no.line_len, &game->texs.no.endian);
	game->texs.so.addr = mlx_get_data_addr(game->texs.so.img,
			&game->texs.so.bpp, &game->texs.so.line_len, &game->texs.so.endian);
	game->texs.we.addr = mlx_get_data_addr(game->texs.we.img,
			&game->texs.we.bpp, &game->texs.we.line_len, &game->texs.we.endian);
	game->texs.dopen.addr = mlx_get_data_addr(game->texs.dopen.img,
			&game->texs.dopen.bpp, &game->texs.dopen.line_len,
			&game->texs.dopen.endian);
	game->texs.dclose.addr = mlx_get_data_addr(game->texs.dclose.img,
			&game->texs.dclose.bpp, &game->texs.dclose.line_len,
			&game->texs.dclose.endian);
	if (game->texs.ea.addr == NULL || game->texs.no.addr == NULL
		|| game->texs.so.addr == NULL || game->texs.we.addr == NULL
		|| game->texs.dopen.addr == NULL || game->texs.dclose.addr == NULL)
		return (pred("GET_DATA_ADDR failed\n", BOLD, 2), -1);
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
		return (free(sc_info->texs), -1);
	mlx_loop_hook(game->mlx, draw_scene, game);
	mlx_hook(game->win, 2, 0, key_hook, game);
	mlx_hook(game->win, 3, 0, key_down_hook, game);
	mlx_hook(game->win, 6, 0, mouse_move, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop(game->mlx);
	return (0);
}
