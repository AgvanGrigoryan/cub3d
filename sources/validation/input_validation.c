
#include "cub3d.h"

int	init_texs_struct(t_scene_info *sc_info)
{
	int	i;

	i = 0;
	sc_info->texs = malloc(sizeof(t_key_value) * 7);
	if (sc_info == NULL)
		return (perror("INIT_TEXTURES"), -1);
	sc_info->texs[0].key = "NO";
	sc_info->texs[1].key = "SO";
	sc_info->texs[2].key = "EA";
	sc_info->texs[3].key = "WE";
	sc_info->texs[4].key = "C";
	sc_info->texs[5].key = "F";
	sc_info->texs[6].key = NULL;
	while (i < 7)
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

void	free_scene_info_struct(t_scene_info *sc_info)
{
	int	i;

	while (i < 7)
		free(sc_info->texs[i++].value);
	free(sc_info->texs);
	sc_info->texs = NULL;
	i = 0;
	if (sc_info->map == NULL)
		return ;
	while (sc_info->map[i] != NULL)
		free(sc_info->map[i++]);
	free(sc_info->map);
	sc_info->map = NULL;
}

int	check_filename(char *scene_file)
{
	int	fn_len;

	fn_len = ft_strlen(scene_file);
	if (fn_len < FN_MIN_LEN
		|| ft_strcmp(scene_file + (fn_len - FN_MIN_LEN), FN_EXT) != 0)
		return (pred("CUB3D: Wrong file name\n", BOLD, 2), -1);
	return (0);
}

int	validation(char *scene_file)
{
	t_scene_info	sc_info;
	int				fd;

	if (scene_file == NULL)
		return (-1);
	if (check_filename(scene_file) == -1)
		return (-1);
	fd = open(scene_file, O_RDONLY);
	if (fd == -1)
		return (perror(scene_file), -1);
	if (init_scene_info_struct(&sc_info) == -1)
		return (1);
	if (parse_scene_file(fd, &sc_info) == -1)
	{
		free_scene_info_struct(&sc_info);
		return (-1);
	}
	return (0);
}
