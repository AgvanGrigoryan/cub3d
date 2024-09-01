/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:22:54 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/01 14:49:21 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	len_of(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	color_validation(char *color)
{
	int					i;
	long long int		num;
	char				**colors;

	if (color[ft_strlen(color) - 1] == ',')
		return (pred("Incorrect color format | xxx,xxx,xxx\n", BOLD, 2), -1);
	colors = ft_split(color, ",");
	if (colors == NULL)
		return (pred("color validation\n", BOLD, 2), -1);
	i = len_of(colors);
	if (i != 3)
		return (pred("Incorrect color format | xxx,xxx,xxx\n", BOLD, 2), -1);
	i = 0;
	while (colors[i] && colors[i] != NULL)
	{
		num = ft_atoi(colors[i]);
		if (num < 0 || num > 255 || num == -1)
			return (pred("Color in range 0,255\n", BOLD, 2), -1);
		i++;
	}
	free_nmatrix(colors, 3);
	return (1);
}

int	are_all_colors_valid(t_scene_info *sc_info)
{
	if (color_validation(sc_info->texs[6].value) == -1
		|| color_validation(sc_info->texs[7].value) == -1)
		return (-1);
	else
		return (1);
}
