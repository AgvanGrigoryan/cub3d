/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:22:54 by natamazy          #+#    #+#             */
/*   Updated: 2024/07/22 21:59:50 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_validation(char *color)
{
	int					i;
	long long int		num;
	char				**colors;

	colors = ft_split(color, ".,");
	i = 0;
	if (i > 3)
		return (pred("Incorrect color format | xxx.xxx.xxx\n", BOLD, 2), -1);
	i = 0;
	while (colors[i] && colors[i] != NULL)
	{
		num = ft_atoi(colors[i]);
		if (num < 0 || num > 255 || num == -1)
			return (pred("Color in range 0,255\n", BOLD, 2), -1);
		i++;
	}
	return (1);
}

int	are_all_colors_valid(t_scene_info *sc_info)
{
	if (color_validation(sc_info->texs[4].value) == -1
		|| color_validation(sc_info->texs[5].value) == -1)
		return (-1);
	else
		return (1);
}
