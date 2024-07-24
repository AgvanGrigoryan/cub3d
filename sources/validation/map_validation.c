/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:43:36 by natamazy          #+#    #+#             */
/*   Updated: 2024/07/24 20:09:59 by natamazy         ###   ########.fr       */
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
	if (&map[i - 1] != NULL && map[i - 1].val[j] != '\0'
		&& map[i - 1].val[j] == '1'
		&& &map[i + 1] != NULL && map[i + 1].val[j]
		&& map[i + 1].val[j] == '1')
		return (0);
	else if (map[i].val[j - 1] && map[i].val[j - 1] == '1'
		&& map[i].val[j + 1] && map[i].val[j + 1] == '1')
		return (0);
	else
		return (-1);
}

int	is_valid_blank(t_line *map, int i, int j)
{
	if (j == 0 || j == map[i].len - 2 || j > map[i - 1].len - 2)
		return (-1);
	if (map[i - 1].len < j || map[i + 1].len < j)
		return (-1);
	if (map[i - 1].val[j] != '\0'
		&& (map[i - 1].val[j] == ' ' || map[i - 1].val[j] == '\0'))
		return (-1);
	if (map[i + 1].val[j] != '\0'
		&& (map[i + 1].val[j] == ' ' || map[i + 1].val[j] == '\0'))
		return (-1);
	if (map[i].val[j - 1] != '\0'
		&& (map[i].val[j - 1] == ' ' || map[i].val[j - 1] == '\0'))
		return (-1);
	if (map[i].val[j + 1] != '\0'
		&& (map[i].val[j + 1] == ' ' || map[i].val[j + 1] == '\0'))
		return (-1);
	return (0);
}

int	is_player(char s, int *pl)
{
	if (s == 'N' || s == 'n'
		|| s == 'S' || s == 's'
		|| s == 'E' || s == 'e'
		|| s == 'W' || s == 'w')
	{
		if (*pl == 0)
			*pl = 1;
		else
			return (-1);
		return (0);
	}
	else
		return (0);
}

int	is_valid_line(t_line *map, int i, int *pl)
{
	int	j;

	j = 0;
	while (map[i].val[j])
	{
		if (map[i].val[j] == '0' && is_valid_blank(map, i, j) == -1)
			return (-1);
		else if (map[i].val[j] == 'D' && is_valid_door(map, i, j) == -1)
			return (-1);
		else if (is_player(map[i].val[j], pl) == -1)
			return (-1);
		j++;
	}
	if (pl == 0)
		return (-1);
	return (0);
}

int	map_validation(t_line *map)
{
	int	i;
	int	pl;
	int	res;

	i = 0;
	pl = 0;
	res = 0;
	while (map[i].val != NULL && res == 0)
	{
		if (i == 0)
			res += is_valid_border(map[i].val);
		else if (map[i + 1].val == NULL)
			res += is_valid_border(map[i].val);
		else if (map[i].len == 1)
			res += is_empty_line(map, i);
		else
			res += is_valid_line(map, i, &pl);
		i++;
	}
	if (res == 0 || pl == 0)
		return (0);
	else
		return (pred("Invalid map\n", BOLD, 2), -1);
}
