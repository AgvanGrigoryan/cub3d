/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:32:05 by natamazy          #+#    #+#             */
/*   Updated: 2024/08/20 18:44:21 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long int	ft_atoi(char *str)
{
	long long int	sum;
	long long int	sign;
	long long int	found;

	sum = 0;
	sign = 1;
	found = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && found)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 10 + *str - '0';
		else
			return (-1);
		str++;
	}
	return (sign * sum);
}

int	is_empty_line(t_line *map, int i)
{
	if (i == 0 || map[i + 1].val != NULL)
		return (-1);
	return (1);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	str_to_trgb(char *str)
{
	char	**tmp;

	tmp = ft_split(str, ",");
	if (tmp == NULL)
		return (-1);
	return (create_trgb(0, ft_atoi(tmp[0]),
			ft_atoi(tmp[1]), ft_atoi(tmp[2])));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	// char * addr_end = img->addr +(WIN_H * img->line_len);
	// if (dst >= img->addr && dst < addr_end
	// 	&& x * (img->bpp / 8) > 0
	// 	&& x * (img->bpp / 8) < img->line_len)
	*(unsigned int *)dst = color;
}
