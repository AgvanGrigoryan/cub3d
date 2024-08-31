/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:59:22 by natamazy          #+#    #+#             */
/*   Updated: 2024/08/31 12:27:52 by natamazy         ###   ########.fr       */
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
# include <math.h>

// Color printing
# define RED				"\033[0;031m"
# define BOLD_RED			"\033[1;031m"
# define BOLD				1
# define NOT_BOLD			0

// Sizes
# define FN_MIN_LEN			4
# define FN_EXT				".cub"

# define TEXS_CNT			6

# define WIN_W				960
# define WIN_H				480

# define ROT_SPEED			0.1
# define MOUSE_ROT_SPEED	0.007

# define CELL_SZ			10

// Keycodes
# define A_KEYCODE			0
# define S_KEYCODE			1
# define D_KEYCODE			2
# define W_KEYCODE			13
# define M_KEYCODE			46
# define E_KEYCODE			14
# define ESC_KEYCODE		53
# define SHIFT_KEYCODE		257
# define LEFT_ARR			123
# define RIGHT_ARR			124

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

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

typedef struct s_texs
{
	t_img	no;
	t_img	so;
	t_img	ea;
	t_img	we;
	t_img	dopen;
	t_img	dclose;
	int		flr;
	int		clg;
}	t_texs;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	walk_speed;
	int		can_run;
}	t_player;

typedef struct s_game_info
{
	int				is_map_mini;
	double			map_rad;
	void			*mlx;
	void			*win;
	t_line			*map;
	t_img			img;
	t_img			torch[8];
	t_texs			texs;
	t_player		pl;
}	t_game_info;

typedef struct s_ray
{
	int			x;
	int			y;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	double		wall_x;
	int			tex_y;
	int			tex_x;
	double		step;
	double		tex_pos;
	t_dpoint	ray_dir;
}	t_ray;

typedef struct s_ipoint
{
	int	x;
	int	y;
}	t_ipoint;

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

// game.c
int				close_game(t_game_info *game);
int				init_textures_img(t_game_info *game, t_scene_info *sc_info);
void			init_player_info(t_line *map, t_player *pl);
int				game_init(t_game_info *game, t_scene_info *sc_info);
int				game_start(t_scene_info *info);

// raycasting.c
int				draw_scene(t_game_info *game);
void			raycasting(t_game_info *game);
void			draw_clg_and_flr(t_game_info *game);
void			process_line(t_ipoint *d, t_ipoint *s,
					t_ipoint *e, t_ipoint *p1);
void			choose_color(t_game_info *game, t_line *map,
					t_ipoint ij, t_dpoint	s);
void			draw_clg_and_flr(t_game_info *game);
void			choose_color(t_game_info *game, t_line *map,
					t_ipoint ij, t_dpoint s);
char			*get_texture(t_game_info *game, int hit,
					int side, t_dpoint ray_dir);
void			raycasting_1(t_game_info *game, t_ray *ray);
void			raycasting_2(t_game_info *game, t_ray *ray);
void			raycasting_3(t_game_info *game, t_ray *ray);

// movement.c
int				mouse_move(int x, int y, t_game_info *game);
void			rotate_view(int keycode, t_player *pl, double rot_angle);
void			move_left(t_line *map, t_player *pl);
void			move_right(t_line *map, t_player *pl);
void			move_back(t_line *map, t_player *pl);
void			move_ahead(t_line *map, t_player *pl);

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
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);

// utils4.c
// ternar for double numbers
double			ternard(int condition, double yes, double no);
void			set_player_dir(char pl_dir, t_player *pl);
void			set_player_pos(t_line *map, t_player *pl);
void			my_mlx_image_clear(t_img *img);
void			open_door(t_game_info *game);
int				key_hook(int key, t_game_info *game);

// utils5.c
int				key_down_hook(int keycode, t_game_info *game);
void			key_hook_1(int key, t_game_info *game);
void			key_hook_2(int key, t_game_info *game);
void			rotate_view(int keycode, t_player *pl, double rot_angle);

// utils6.c
void			get_torch_textures(t_game_info *game);
void			draw_player_helper(t_game_info *game,
					t_dpoint *l_dir, t_dpoint *r_dir);

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

// torch_anim.c
void			torch_anim(t_game_info *game);
void			set_torch_textures(t_game_info *game);
int				destroy_torch_imgs(void *mlx, t_img *torch);

// game.c
int				destroy_texs_imgs(void *mlx, t_texs *texs);
int				check_texs_img(t_texs *texs);
int				get_textures_data(t_game_info *game);

// draw.c
void			draw_mini_map(t_game_info *game);
void			draw_square(t_img *img, t_ipoint xy, int size, int color);
void			draw_player(t_game_info *game, double s_i, double s_j);
int				draw_scene(t_game_info *game);
void			draw_line(t_ipoint p1, t_ipoint p2, int color, t_img *img);

#endif