/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:15:40 by natamazy          #+#    #+#             */
/*   Updated: 2024/07/23 13:21:19 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_validation(char *texture)
{
	int	fd;
	int	len;

	fd = open(texture, O_RDONLY);
	close(fd);
	len = ft_strlen(texture);
	if (len < 4 || texture[len - 1] != 'm' || texture[len - 2] != 'p'
		|| texture[len - 3] != 'x' || texture[len - 4] != '.')
		return (pred("File format is not xpm - ", BOLD, 2),
			pred(texture, BOLD, 2), printf("\n"), -1);
	if (fd > 2)
		return (1);
	else
		return (pred("File not found - ", BOLD, 2),
			pred(texture, BOLD, 2), printf("\n"), -1);
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
