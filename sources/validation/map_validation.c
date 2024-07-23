/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:43:36 by natamazy          #+#    #+#             */
/*   Updated: 2024/07/23 18:50:25 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_border(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == ' ')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	is_valid_door(t_line *map, int i, int j)
{
	if (&map[i - 1] != NULL && map[i - 1].val[j] != '\0' && map[i - 1].val[j] == '1'
		&& &map[i + 1] != NULL && map[i + 1].val[j] && map[i + 1].val[j] == '1')
		return (0);
	else if (map[i].val[j - 1] && map[i].val[j - 1] == '1'
		&& map[i].val[j + 1] && map[i].val[j + 1] == '1')
		return (0);
	else
		return (-1);
}

int	is_valid_blank(t_line *map, int i, int j)
{
	if (j == 0 || j == map[i].len - 2)
		return (-1);
	if (map[i - 1].len < j || map[i + 1].len < j)
		return (-1);
	if (map[i - 1].val[j] != '\0' && (map[i - 1].val[j] == ' ' || map[i - 1].val[j] == '\0'))
		return (-1);
	if (map[i + 1].val[j] != '\0' && (map[i + 1].val[j] == ' ' || map[i + 1].val[j] == '\0'))
		return (-1);
	if (map[i].val[j - 1] != '\0' && (map[i].val[j - 1] == ' ' || map[i].val[j - 1] == '\0'))
		return (-1);
	if (map[i].val[j + 1] != '\0' && (map[i].val[j + 1] == ' ' || map[i].val[j + 1] == '\0'))
		return (-1);
	return (0);
}

int	is_valid_line(t_line *map, int i)
{
	int	j;

	j = 0;
	while (map[i].val[j])
	{
		if (map[i].val[j] == '0' && is_valid_blank(map, i, j) == -1)
			return (-1);
		else if (map[i].val[j] == 'D' && is_valid_door(map, i, j) == -1)
			return (-1);
		j++;
	}
	return (0);
}

int	map_validation(t_line *map)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (map[i].val != NULL && res == 0)
	{
		if (i == 0)
			res += is_valid_border(map[i].val);
		else if (map[i + 1].val == NULL)
			res += is_valid_border(map[i].val);
		else
			res += is_valid_line(map, i);
		printf("last map %s %d line - %d\n", map[i].val, res, i);
		i++;
	}
	if (res == 0)
		return (0);
	else
		return (pred("Invalid map\n", BOLD, 2), -1);
}
