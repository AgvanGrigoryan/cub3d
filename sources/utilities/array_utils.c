
#include "cub3d.h"

// The function of adding a value to an array makes the array dynamic
//arguments:
//		data - current array
//		length - current length of elements
//		capacity - max length of elements in this array
//		value - new value of array
int	append(t_dyn_arr *arr, char *value)
{
	char	**new_arr;
	int		i;

	if (arr->length >= arr->capacity)
	{
		new_arr = malloc(sizeof(char *) * 2 * arr->capacity);
		if (new_arr == NULL)
			return (perror("DYN_ARR_APPEND"), -1);
		arr->capacity *= 2;
		i = 0;
		while (i < arr->length)
		{
			new_arr[i] = arr->arr[i];
			i++;
		}
		free(arr->arr);
		arr->arr = new_arr;
	}
	arr->arr[arr->length] = value;
	(arr->length)++;
	return (0);
}

t_dyn_arr	*create_dyn_arr(void)
{
	t_dyn_arr	*dyn_arr;

	dyn_arr = malloc(sizeof(t_dyn_arr));
	if (dyn_arr == NULL)
		return (perror("CREATE_DYN_ARR"), NULL);
	dyn_arr->arr = malloc(sizeof(char *));
	if (dyn_arr->arr == NULL)
		return (perror("CREATE_DYN_ARR"), NULL);
	dyn_arr->capacity = 1;
	dyn_arr->length = 0;
	return (dyn_arr);
}
