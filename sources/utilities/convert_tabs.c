/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:40:14 by natamazy          #+#    #+#             */
/*   Updated: 2024/07/23 17:40:45 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_map(t_line *map)
{
	int	i;

	i = 0;
	while (map[i].val != NULL)
		free(map[i].val);
	free(map);
}

int	count_char(const char *str, char sym)
{
	int	cnt;

	cnt = 0;
	while (str && *str)
	{
		if (*str == sym)
			cnt++;
		str++;
	}
	return (cnt);
}

char	*replace_tabs(char *str, t_line	*line)
{
	int		i;
	char	*res;
	int		new_len;
	int		tabs;

	tabs = count_char(str, '\t');
	new_len = ft_strlen(str) - tabs + (tabs * 4);
	res = (char *)malloc((new_len + 1));
	if (res == NULL)
		return (perror("REPLACE_TABS"), NULL);
	i = 0;
	while (*str)
	{
		if (*str == '\t' && ft_memset(res + i, ' ', 4))
			i += 4;
		else
			res[i++] = *str;
		str++;
	}
	res[i] = '\0';
	line->len = new_len;
	return (res);
}

t_line	*get_converted_map(t_dyn_arr *buf)
{
	t_line	*map;
	int		map_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < buf->length && starts_with_digit(buf->arr[i]) == 0)
		i++;
	map_len = buf->length - i;
	map = malloc(sizeof(t_line) * (map_len + 1));
	if (map == NULL)
		return (perror("GET_MAP"), NULL);
	while (j < map_len)
	{
		map[j].val = replace_tabs(buf->arr[i], map + j);
		if (map[j].val == NULL)
			return (free_map(map), NULL);
		i++;
		j++;
	}
	map[j].val = NULL;
	return (map);
}
