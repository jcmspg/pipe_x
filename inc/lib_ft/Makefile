# Color codes
RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NOCOLOR = \033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Name of the library
NAME = libft.a

# Directories
SRC_DIR = .
OBJ_DIR = ./obj

# Gather all .c files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Convert source files to object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Header files (in case you need to specify them)
HEADERS = libft.h ft_printf.h get_next_line.h

# Rule to compile .c into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create the library from object files
$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)
	@echo "$(YELLOW)Building library...$(NOCOLOR)"
	@echo "$(GREEN)$(NAME) created successfully.$(NOCOLOR)"

# Build everything
all: $(NAME)

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Object files removed.$(NOCOLOR)"

# Clean object files and the library
fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)$(NAME) removed.$(NOCOLOR)"

# Rebuild the library
re: fclean all

.PHONY: all clean fclean re

