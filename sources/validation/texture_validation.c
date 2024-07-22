/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:15:40 by natamazy          #+#    #+#             */
/*   Updated: 2024/07/22 19:55:59 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Function for texture validation
int	texture_validation(char *texture)
{
	int	fd;

	fd = open(texture, O_RDONLY);
	close(fd);
	if (fd > 2)
		return (1);
	else
		return (-1);
}

int	are_all_textures_valid(t_scene_info *sc_info)
{
	if (texture_validation(sc_info->texs[0].value) == -1
		|| texture_validation(sc_info->texs[1].value) == -1
		|| texture_validation(sc_info->texs[2].value) == -1
		|| texture_validation(sc_info->texs[3].value) == -1)
		return (-1);
	else
		return (1);
}
