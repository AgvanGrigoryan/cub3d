/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:56:06 by root              #+#    #+#             */
/*   Updated: 2024/07/18 17:15:50 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_texs_struct(t_scene_info *sc_info)
{
	int	i;

	i = 0;
	sc_info->texs = malloc(sizeof(t_key_value) * (6 + 1));
	if (sc_info == NULL)
		return (perror("CUB3D"), -1);
	sc_info->texs[0].key = "NO";
	sc_info->texs[1].key = "SO";
	sc_info->texs[2].key = "EA";
	sc_info->texs[3].key = "WE";
	sc_info->texs[4].key = "C";
	sc_info->texs[5].key = "F";
	while (i < 6)
		sc_info->texs[i++].value = NULL;
	return (0);
}

int	init_scene_info_struct(t_scene_info *sc_info)
{
	if (init_texs_struct(sc_info) == -1)
		return (-1);
	sc_info->map = NULL;
	return (0);
}

int	validation(char *scene_file)
{
	t_scene_info	sc_info;
	int				fn_len;
	int				fd;

	if (scene_file == NULL)
		return (-1);
	fn_len = ft_strlen(scene_file);
	if (fn_len < FN_MIN_LEN
		|| ft_strcmp(scene_file + (fn_len - FN_MIN_LEN), FN_EXT) != 0)
		return (pred("CUB3D: Wrong file name\n", BOLD, 2), -1);
	if (init_scene_info_struct(&sc_info) == -1)
		return (1);
	fd = open(scene_file, O_RDONLY);
	if (fd == -1)
		return (perror(scene_file), -1);
	printf("MESSAGE: INPUT VALIDATION IS PASSED\n");
	if (parse_scene_file(fd, &sc_info) == -1)
		return (pred("CUB3D: Invalid scene file\n", BOLD, 2), -1);
	return (0);
}
