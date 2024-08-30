/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torchanim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:55:48 by natamazy          #+#    #+#             */
/*   Updated: 2024/08/30 19:29:23 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

unsigned int	my_mlx_color_taker(t_img *data, int j, int i)
{
	char			*dst;

	if (j >= 0 && j < data->w && i >= 0 && i < data->h)
	{
		dst = data->addr + (i * data->line_len
				+ j * (data->bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

void	print_torch(t_game_info *game, int i)
{
	int				x;
	int				y;
	int				px;
	int				py;
	unsigned int	color;

	px = 0;
	x = WIN_W / 2 - game->torch[i].w / 2 - 1;
	while (++x < WIN_W / 2 + game->torch[i].w / 2)
	{
		y = WIN_H - game->torch[i].h - 1;
		py = 0;
		while (++y < WIN_H)
		{
			color = my_mlx_color_taker(&game->torch[i], px, py);

			if (color == 4278190080)
				color = my_mlx_color_taker(&game->img, x, y);

			my_mlx_pixel_put(&game->img, x, y, color);
			py++;
		}
		px++;
	}
}

void	torch_anim(t_game_info *game)
{
	static int	i;
	static int	count;

	if (count % 7 == 0)
	{
		i++;
		if (i == 8)
			i = 0;
	}
	print_torch(game, i);
	count++;
	if (count >= 1000)
		count = 0;
}

int	destroy_torch_imgs(void *mlx, t_img *torch)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (torch[i].img != NULL
			&& mlx_destroy_image(mlx, torch[i].img) == -1)
			return (-1);
	}
	return (0);
}

void	set_torch_textures(t_game_info *game)
{
	game->torch[0].img = mlx_xpm_file_to_image(game->mlx,
			"./torchanim/1.xpm", &game->torch[0].w,
			&game->torch[0].h);
	game->torch[1].img = mlx_xpm_file_to_image(game->mlx,
			"./torchanim/2.xpm", &game->torch[1].w,
			&game->torch[1].h);
	game->torch[2].img = mlx_xpm_file_to_image(game->mlx,
			"./torchanim/3.xpm", &game->torch[2].w,
			&game->torch[2].h);
	game->torch[3].img = mlx_xpm_file_to_image(game->mlx,
			"./torchanim/4.xpm", &game->torch[3].w,
			&game->torch[3].h);
	game->torch[4].img = mlx_xpm_file_to_image(game->mlx,
			"./torchanim/5.xpm", &game->torch[4].w,
			&game->torch[4].h);
	game->torch[5].img = mlx_xpm_file_to_image(game->mlx,
			"./torchanim/6.xpm", &game->torch[5].w,
			&game->torch[5].h);
	game->torch[6].img = mlx_xpm_file_to_image(game->mlx,
			"./torchanim/7.xpm", &game->torch[6].w,
			&game->torch[6].h);
	game->torch[7].img = mlx_xpm_file_to_image(game->mlx,
			"./torchanim/8.xpm", &game->torch[7].w,
			&game->torch[7].h);
}

void	get_torch_textures(t_game_info *game)
{
	int	i;

	set_torch_textures(game);
	if (!game->torch[0].img || !game->torch[1].img
		|| !game->torch[2].img || !game->torch[3].img
		|| !game->torch[4].img || !game->torch[5].img
		|| !game->torch[6].img || !game->torch[7].img)
		destroy_torch_imgs(game->mlx, game->torch);
	i = -1;
	while (++i < 8)
	{
		game->torch[i].addr = mlx_get_data_addr(game->torch[i].img,
				&game->torch[i].bpp, &game->torch[i].line_len,
				&game->torch[i].endian);
		if (!game->torch[i].addr)
			destroy_torch_imgs(game->mlx, game->torch);
	}
}
