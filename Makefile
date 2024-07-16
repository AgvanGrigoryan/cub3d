# Project name
NAME = cub3d

# Readline name
READLINE = readline

# Compilator
CC = cc

# Compilator flags
INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
CFLAGS = -Wall -Wextra -Werror $(INC_DIRS) #-g3 -fsanitize=address

# Headers
HEADERS = 	includes/cub3d.h

# Source directory
SRCS_DIR = sources/

# Objects directory
OBJS_DIR = objects/

# Source file names
SRCS_NAME = main.c utilities/utils1.c

# Objects file names
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

# Compilation process
all: $(NAME)

linux_minishell: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/utilities
	$(CC) $(CFLAGS) -c $< -o $@

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