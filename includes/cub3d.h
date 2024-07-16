/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:54:00 by aggrigor          #+#    #+#             */
/*   Updated: 2024/07/16 13:54:10 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
/*
allowed functions:
open, close, read, write,
printf, malloc, free, perror,
strerror, exit, math functions
*/

# include <stdio.h>
# include <unistd.h>

# define RED	"\033[0;031m"
# define BOLD_RED	"\033[1;031m"
# define BOLD 1
# define NOT_BOLD 0

// utils1.c
void	pred(char *str, int is_bold, int fd);

#endif