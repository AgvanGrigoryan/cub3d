/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:59:22 by natamazy          #+#    #+#             */
/*   Updated: 2024/08/05 21:19:16 by aggrigor         ###   ########.fr       */
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
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>

// colored printing
# define RED	"\033[0;031m"
# define BOLD_RED	"\033[1;031m"
# define BOLD 1
# define NOT_BOLD 0

# define FN_MIN_LEN 4
# define FN_EXT ".cub"

# define WIN_W 1080
# define WIN_H 920
typedef struct s_line
{
	char	*val;
	int		len;
}	t_line;

typedef struct s_map
{
	t_line	*lines;
	int		size;
}	t_map;

typedef struct s_key_value
{
	char	*key;
	char	*value;
}	t_key_value;

typedef struct s_scene_info
{
	t_key_value	*texs;
	t_line		*map;
}	t_scene_info;

typedef struct s_img
{
	int		h;
	int		w;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

// typedef struct s_trgb
// {
// 	int	t;
// 	int	r;
// 	int	g;
// 	int	b;
// }	t_trgb;

typedef struct s_texs
{
	t_img	no;
	t_img	so;
	t_img	ea;
	t_img	we;
	int		flr;
	int		clg;
}	t_texs;

typedef struct s_game_info
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_texs			texs;
	t_line			*map;
}	t_game_info;

// arr - dynamic string matrix
// length - current length of elements
// capacity - max length of elements in this array
typedef struct s_dyn_arr
{
	char	**arr;
	int		length;
	int		capacity;
}	t_dyn_arr;

// main.c

// game_start.c
int	game_start(t_scene_info *info);

// color_validation.c
int				are_all_colors_valid(t_scene_info *sc_info);

// input_validation.c
void			free_scene_info_struct(t_scene_info *sc_info);
int				validation(char *scene_file, t_scene_info *sc_info);
int				check_filename(char *scene_file);
int				init_texs_struct(t_scene_info *sc_info);
int				init_scene_info_struct(t_scene_info *sc_info);

// player_validation.c
int				is_player(char s, int *pl);

// scene_validation.c
void			remove_extra_lines(t_dyn_arr *buf);
int				map_validation(t_line *map);
int				parse_scene_file(int fd, t_scene_info *sc_info);
int				set_texures_info(t_scene_info *sc_info, t_dyn_arr *buf);
int				validate_scene_file(t_scene_info *sc_info, t_dyn_arr *buf);

// texture_validation.c
int				are_all_textures_valid(t_scene_info *sc_info);

// utils1.c
unsigned long	arrlen(char **arr);
unsigned long	ft_strlen(const char *s);
void			free_nmatrix(char **matrix, int n);
void			pred(char *str, int is_bold, int fd);
int				ft_strcmp(const char *s1, const char *s2);

// utils2.c
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_isdigit(int c);
int				ft_isspace(char c);
int				is_only_spaces(const char *str);
int				starts_with_digit(const char *str);

// utils3.c
long long int	ft_atoi(char *str);
int				is_empty_line(t_line *map, int i);
int				create_trgb(int t, int r, int g, int b);
int				str_to_trgb(char *str);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

// array_utils.c
t_dyn_arr		*create_dyn_arr(void);
int				pop(t_dyn_arr *arr, int index);
int				append(t_dyn_arr *arr, char *value);

// convert_tabs.c
t_line			*get_converted_map(t_dyn_arr *buf);

// key_value_utils.c
char			*get_value(t_key_value *arr, char *key);
int				set_value(t_key_value *arr, char *key, char *value);

// get_next_line.c
char			*get_next_line(int fd);

// ft_split.c
char			**ft_split(char const *s, char *seps);

#endif
