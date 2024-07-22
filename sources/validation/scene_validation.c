
#include "cub3d.h"
#include "get_next_line.h"

int	parse_scene_file(int fd, t_scene_info *sc_info)
{
	t_dyn_arr	*buf;
	char		*next_line;

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
	if (validate_scene_file(sc_info, buf) == 0)
		return (0);
	pred("CUB3D: Validation failed\n", BOLD, 2);
	free_nmatrix(buf->arr, buf->length);
	return (-1);
}

void	remove_extra_lines(t_dyn_arr *buf)
{
	int	i;

	i = 0;
	printf("LEN:%d\n", buf->length);
	while (i < buf->length && starts_with_digit(buf->arr[i]) == 0)
	{
		if (is_only_spaces(buf->arr[i]) == 1)
			pop(buf, i);
		else
			i++;
	}
	i = buf->length - 1;
	while (i >= 0 && is_only_spaces(buf->arr[i]) == 1)
	{
		pop(buf, i);
		i--;
	}
}
int	validate_scene_file(t_scene_info *sc_info, t_dyn_arr *buf)
{
	remove_extra_lines(buf);
	printf("\n\033[0;33mWARNING: MAP VALIDATION IS NOT COMPLETED\033[0m\n");
	if (buf == NULL || buf->length < 1) // maybe will change min length of buf
		return (pred("Invalid scene file\n", BOLD, 2), -1);
	if (set_texures_info(sc_info, buf) == -1)
		return (-1);
	// 1.check if the textures values is valid or not, 
	//OR Check them at each iteration of the while loop before set values
	if (map_validation(sc_info, buf) == -1)
		return (-1);
	return (0);
}

int	set_texures_info(t_scene_info *sc_info, t_dyn_arr *buf)
{
	int		i;
	char	**splited;

	i = 0;
	while (i < buf->length && starts_with_digit(buf->arr[i]) == 0)
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

int	map_validation(t_scene_info *sc_info, t_dyn_arr *buf)
{
	int i = 0;
	(void)sc_info;
	// 2.Set map in sc_info->map
	while (i < buf->length && starts_with_digit(buf->arr[i]) == 0)
		i++;
	printf("MAP:MAP:MAP:MAP:MAP:MAP\n");
	for (; i < buf->length; i++)
		printf("%d:\t[%s", i, buf->arr[i]);
	return (0);
}
