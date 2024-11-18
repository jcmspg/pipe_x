# Colors
RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NOCOLOR = \033[0m

# Name of the project
NAME = pipex

# Compiler
CC = cc

# Flags
CFLAGS = -Wall -Wextra -Werror -g
POSTCC = -I $(INC_DIR)

# Sources
SRC_DRC = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc
BONUS_DIR = ./bonus

# Files
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
BONUS_FILES = $(shell find $(BONUS_DIR) -name "*.c")

# Object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to compile .c into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(POSTCC) -c $< -o $@
	@echo "$(CYAN)Compiling:$(NOCOLOR) $<"

# Rule to compile the project
$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	@echo "$(YELLOW)Building project...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(POSTCC) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)Project built successfully.$(NO_COLOR)"

# Rule to build the included library
$(LIBS):
	@echo "$(YELLOW)Building libraries...$(NO_COLOR)"
	@make -C $(INC_DIR)/lib_ft > /dev/null 2>&1 || { echo -e "$(RED)Failed to build lib_ft$(NO_COLOR)"; exit 1; }
	@make -C $(INC_DIR)/ft_printf > /dev/null 2>&1 || { echo -e "$(RED)Failed to build ft_printf$(NO_COLOR)"; exit 1; }
	@echo "$(GREEN)Libraries built successfully.$(NO_COLOR)"

# Rule to build bonus
$(BONUS): $(OBJ_DIR) $(OBJ_FILES)
	@echo "$(YELLOW)Building bonus...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(POSTCC) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)Bonus built successfully.$(NO_COLOR)"


# build only the library
libs: $(LIBS)

# build the project
build: $(NAME)

# build bonus
bonus: $(BONUS)

# build all
all: libs build bonus

# clean the object files
clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(INC_DIR)/lib_ft
	@make clean -C $(INC_DIR)/ft_printf
	@echo "$(BLUE)Object files removed.$(NO_COLOR)"

# clean the object files and the project
fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(INC_DIR)/lib_ft
	@make fclean -C $(INC_DIR)/ft_printf
	@echo "$(BLUE)Project removed.$(NO_COLOR)"

# clean and rebuild the project
re: fclean all

# run the project
run: build
	@./$(NAME)

.PHONY: all clean fclean re run libs build bonus
