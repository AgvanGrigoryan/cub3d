# Project name
NAME = cub3D

# Readline name
READLINE = readline

# Compilator
CC = cc

# Compilator flags
INC_DIRS = -I./includes -I./mlx
LDFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
CFLAGS = $(INC_DIRS) #-Wall -Wextra -Werror $(INC_DIRS) -g3 -fsanitize=address


# Headers
HEADERS = includes/cub3d.h includes/get_next_line.h

# Source directory
SRCS_DIR = sources/

# Objects directory
OBJS_DIR = objects/

# Source file names
SRCS_NAME = main.c \
			utilities/ft_split.c \
			utilities/utils1.c \
			utilities/utils2.c \
			utilities/utils3.c \
			utilities/utils4.c \
			utilities/array_utils.c \
			utilities/convert_tabs.c \
			utilities/key_value_utils.c \
			utilities/get_next_line.c \
			utilities/get_next_line_utils.c \
			validation/input_validation.c \
			validation/map_validation.c \
			validation/player_validation.c \
			validation/scene_validation.c \
			validation/texture_validation.c \
			validation/color_validation.c \
			gameplay/game.c\
			gameplay/raycasting.c\
			gameplay/movement.c

# Objects file names
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

# Compilation process
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/utilities
	@mkdir -p $(OBJS_DIR)/validation
	@mkdir -p $(OBJS_DIR)/gameplay
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	@$(RM) $(OBJS)

# Force cleaning
fclean: clean
	@$(RM) $(NAME)
	rm -rf $(OBJS_DIR)

# Remaking
re: fclean all

# PHONY files
.PHONY: all clean fclean re
