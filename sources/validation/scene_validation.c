/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:22:48 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/02 21:40:33 by aggrigor         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"
#include "get_next_line.h"

int	parse_scene_file(int fd, t_scene_info *sc_info)
{
	t_dyn_arr	*buf;
	char		*next_line;

	buf = create_dyn_arr();
	while (true)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		if (append(buf, next_line) == -1)
		{
			free_nmatrix(buf->arr, buf->length);
			free(buf);
			return (-1);
		}
	}
	if (validate_scene_file(sc_info, buf) == 0)
	{
		free_nmatrix(buf->arr, buf->length);
		free(buf);
		return (0);
	}
	pred("cub3D: Validation failed\n", BOLD, 2);
	free_nmatrix(buf->arr, buf->length);
	free(buf);
	return (-1);
}

void	remove_extra_lines(t_dyn_arr *buf)
{
	int	i;

	i = 0;
	while (i < buf->length && starts_with_digit(buf->arr[i]) == 0)
	{
		if (is_only_spaces(buf->arr[i]) == 1)
			pop(buf, i);
		else
			i++;
	}
	i = buf->length - 1;
	while (i >= 0 && is_only_spaces(buf->arr[i]) == 1)
	{
		pop(buf, i);
		i--;
	}
}

int	validate_scene_file(t_scene_info *sc_info, t_dyn_arr *buf)
{
	remove_extra_lines(buf);
	if (buf == NULL || buf->length < 1)
		return (pred("Invalid scene file\n", BOLD, 2), -1);
	if (set_texures_info(sc_info, buf) == -1)
		return (-1);
	if (are_all_colors_valid(sc_info) == -1)
		return (-1);
	if (are_all_textures_valid(sc_info) == -1)
		return (-1);
	sc_info->map = get_converted_map(buf, 0, 0);
	if (sc_info->map == NULL)
		return (-1);
	if (map_validation(sc_info->map) == -1)
		return (-1);
	return (0);
}

int	set_texures_info(t_scene_info *sc_info, t_dyn_arr *buf)
{
	int		i;
	char	**splited;

	i = 0;
	while (i < buf->length && starts_with_digit(buf->arr[i]) == 0)
	{
		splited = ft_split(buf->arr[i], " \t\n");
		if (splited == NULL)
			return (-1);
		else if (arrlen(splited) != 2)
			return (pred("Incorrect texture format\n", BOLD, 2),
				free_nmatrix(splited, arrlen(splited)), -1);
		if (get_value(sc_info->texs, splited[0]) == NULL)
		{
			if (set_value(sc_info->texs, splited[0], splited[1]) == -1)
				return (pred("Unknown texture title\n", BOLD, 2),
					free_nmatrix(splited, arrlen(splited)), -1);
		}
		else
			return (pred("Duplication of texture info\n", BOLD, 2),
				free(splited), -1);
		free(splited[0]);
		free(splited);
		i++;
	}
	return (0);
}
