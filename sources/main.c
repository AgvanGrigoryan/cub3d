
#include <stdio.h>
#include "cub3d.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (pred("Error: ./cub3d <filename>.cub\n", BOLD, 2), 1);
	if (validation(argv[1]) == -1)
		return (1);
	printf("FILENAME:%s\n", argv[1]);
	return (0);
}
