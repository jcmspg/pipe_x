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
POSTCC = -I $(INC_DIR) -L $(LIB_DIR) -lft

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc
BONUS_DIR = ./bonus
LIB_DIR = $(INC_DIR)/lib_ft

# Source and bonus files
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
	@echo "$(YELLOW)Building project...$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(POSTCC) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)Project built successfully.$(NOCOLOR)"

# Rule to build the included library
LIBS = $(LIB_DIR)/libft.a

$(LIBS):
	@echo "$(YELLOW)Building libraries...$(NOCOLOR)"
	@make -s -C $(LIB_DIR) all || { echo -e "$(RED)Failed to build lib_ft$(NOCOLOR)"; exit 1; }
	@echo "$(GREEN)Libraries built successfully.$(NOCOLOR)"

# Rule to build bonus
$(BONUS): $(OBJ_DIR) $(OBJ_FILES)
	@echo "$(YELLOW)Building bonus...$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(POSTCC) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)Bonus built successfully.$(NOCOLOR)"

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
	@make clean -C $(LIB_DIR)
	@echo "$(BLUE)Object files removed.$(NOCOLOR)"

# clean the object files and the project
fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)
	@echo "$(BLUE)Project removed.$(NOCOLOR)"

# clean and rebuild the project
re: fclean all

# run the project
run: build
	@./$(NAME)

.PHONY: all clean fclean re run libs build bonus
#s build bonus
