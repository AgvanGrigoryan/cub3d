/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:33:09 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/10 15:21:11 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "mlx.h"

int	main(int argc, char *argv[])
{
	t_scene_info	sc_info;

	if (argc != 2)
	{
			
		pred("Error: ./cub3d <filename>.cub\n", BOLD, 2);
		system("leaks cub3D");
		return (1);	
	}
	if (validation(argv[1], &sc_info) == -1)
	{
		system("leaks cub3D");
		return (1);
	}
	game_start(&sc_info);
	free_scene_info_struct(&sc_info);
	return (0);
}
