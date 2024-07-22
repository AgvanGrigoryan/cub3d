/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:23:03 by natamazy          #+#    #+#             */
/*   Updated: 2024/07/22 18:23:20 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_value(t_key_value *arr, char *key)
{
	int	i;

	i = 0;
	if (arr == NULL || key == NULL)
		return (NULL);
	while (arr[i].key != NULL && ft_strcmp(arr[i].key, key) != 0)
		i++;
	return (arr[i].value);
}

int	set_value(t_key_value *arr, char *key, char *value)
{
	int	i;

	i = 0;
	if (arr == NULL || key == NULL)
		return (-1);
	while (arr[i].key != NULL && ft_strcmp(arr[i].key, key) != 0)
		i++;
	if (arr[i].key == NULL)
		return (-1);
	arr[i].value = value;
	return (0);
}
