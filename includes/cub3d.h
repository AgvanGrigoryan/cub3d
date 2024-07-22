
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

typedef struct s_key_value
{
	char	*key;
	char	*value;
}	t_key_value;

typedef struct s_scene_info
{
	t_key_value	*texs;
	char		**map;
}	t_scene_info;

typedef struct s_dyn_arr
{
	char	**arr;
	int		length;
	int		capacity;
}	t_dyn_arr;

//input_validation.c
int				init_texs_struct(t_scene_info *sc_info);
int				init_scene_info_struct(t_scene_info *sc_info);
void			free_scene_info_struct(t_scene_info *sc_info);
int				check_filename(char *scene_file);
int				validation(char *scene_file);

//scene_validation.c
int				parse_scene_file(int fd, t_scene_info *sc_info);
int				validate_scene_file(t_scene_info *sc_info, t_dyn_arr *buf);
int				set_texures_info(t_scene_info *sc_info, t_dyn_arr *buf);

// utils1.c
void			pred(char *str, int is_bold, int fd);
int				ft_strcmp(const char *s1, const char *s2);
unsigned long	ft_strlen(const char *s);
void			free_nmatrix(char **matrix, int n);
unsigned long	arrlen(char **arr);

// utils2.c
char			*ft_substr(char const *s, unsigned int start, size_t len);

// array_utils.c
int				append(t_dyn_arr *arr, char *value);
t_dyn_arr		*create_dyn_arr(void);

// key_value_utils.c
char			*get_value(t_key_value *arr, char *key);
int				set_value(t_key_value *arr, char *key, char *value);

// get_next_line.c
char			*get_next_line(int fd);

// ft_split.c
char			**ft_split(char const *s, char *seps);
#endif
