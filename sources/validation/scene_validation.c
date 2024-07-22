
#include "cub3d.h"
#include "get_next_line.h"

int	parse_scene_file(int fd, t_scene_info *sc_info)
{
	t_dyn_arr	*buf;
	char		*next_line;
	int			is_valid;

	is_valid = 0;
	buf = create_dyn_arr();
	while (true)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		if (append(buf, next_line) == -1)
		{
			free_nmatrix(buf->arr, buf->length);
			free(buf);
			return (-1);
		}
	}
	is_valid = validate_scene_file(sc_info, buf);
	if (is_valid == -1)
	{
		pred("CUB3D: Validation failed\n", BOLD, 2);
		free_nmatrix(buf->arr, buf->length);
	}
	return (is_valid);
}

int	validate_scene_file(t_scene_info *sc_info, t_dyn_arr *buf)
{
	printf("\n\033[0;33mWARNING: MAP VALIDATION IS NOT COMPLETED\033[0m\n");
	if (buf == NULL || buf->length < 1) // maybe will change min length of buf
		return (pred("Invalid scene file\n", BOLD, 2), -1);
	printf("\n\033[0;33mWARNING 2: THE BUFFER IS NOT TRIM OR SPLIT BEFORE CHECKING. A FORMAT ERROR 'Incorrect texture format' OCCURS WHEN A NEW LINE IS INSERTED IN THE FILE \033[0m\n");
	if (set_texures_info(sc_info, buf) == -1)
		return (-1);
	// 1.check if the textures values is valid or not OR Check them at each iteration of the while loop before set values
	// 2.Set map in sc_info->map
	return (0);
}

int	set_texures_info(t_scene_info *sc_info, t_dyn_arr *buf)
{
	int		i;
	char	**splited;

	i = 0;
	while (i < buf->length)
	{
		splited = ft_split(buf->arr[i], " \t");
		if (splited == NULL || arrlen(splited) != 2)
			return (pred("Incorrect texture format\n", BOLD, 2), free(splited), -1);
		if (get_value(sc_info->texs, splited[0]) == NULL)
		{
			if (set_value(sc_info->texs, splited[0], splited[1]) == -1)
				return (pred("Unknown texture title\n", BOLD, 2), free(splited), -1);
		}
		else
			return (pred("Duplication of texture info\n", BOLD, 2), free(splited), -1);
		free(splited);
		i++;
	}
	return (0);
}
