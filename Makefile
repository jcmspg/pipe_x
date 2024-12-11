
# build all
all: libs build bonus

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
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
POSTCC = -I $(INC_DIR) -I $(LIB_DIR) 
# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc
LIB_DIR = $(INC_DIR)/lib_ft

# Rule to build the included library
LIBS = $(LIB_DIR)/libft.a

# Source and bonus files
SRC_FILES = $(SRC_DIR)/free_utils.c\
			$(SRC_DIR)/parse_utils2.c\
			$(SRC_DIR)/here_doc.c\
			$(SRC_DIR)/here_doc_utils.c\
			$(SRC_DIR)/main.c\
			$(SRC_DIR)/parse_utils4.c\
			$(SRC_DIR)/here_doc_utils2.c\
			$(SRC_DIR)/checker_utils.c\
			$(SRC_DIR)/checker_utils_hd.c\
			$(SRC_DIR)/parse_utils3.c\
			$(SRC_DIR)/pipe_utils.c\
			$(SRC_DIR)/pipe_utils2.c\
			$(SRC_DIR)/pipex.c\
			$(SRC_DIR)/security.c\
			$(SRC_DIR)/validation.c\
			$(SRC_DIR)/init_utils.c\
			$(SRC_DIR)/parse_utils.c\
			$(SRC_DIR)/debug_utils.c\
			$(SRC_DIR)/init_utils2.c\
			$(SRC_DIR)/security2.c\


# Object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Object files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Function to print the loading bar
define print_bar
	@echo -n "\r$(CYAN)[$(1)%%] $(2) $(NOCOLOR)"
endef

# Rule to compile .c into .o with progress bar
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval FILE_COUNT=$(words $(SRC_FILES)))
	@$(eval FILE_NUM=$(words $(OBJ_FILES) - $(FILE_COUNT)))
	@$(eval PERCENT=$$(($$(FILE_NUM) * 100 / $$(FILE_COUNT))))
	@$(CC) $(CFLAGS) $(POSTCC) -c $< -o $@
	@$(call print_bar, $(PERCENT), "Compiling: $<")

# Rule to compile the included library
$(LIBS):
	@make -C $(LIB_DIR) > /dev/null 2>&1
	@echo "$(GREEN)Library built successfully.$(NOCOLOR)"

# Rule to compile the project
$(NAME): $(OBJ_DIR) $(OBJ_FILES) 
	@echo "$(YELLOW)Building project...$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(POSTCC)  $(OBJ_FILES) -o $(NAME) $(LIBS)
	@echo "$(GREEN)Project built successfully.$(NOCOLOR)"



# build only the library
libs: $(LIBS)

# build the project
build: $(LIBS) $(NAME)

# clean the object files
clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR) > /dev/null 2>&1
	@echo "$(BLUE)Object files removed.$(NOCOLOR)"
	@echo "$(GREEN)Clean done.$(NOCOLOR)"

# clean the object files and the project
fclean: clean
	@rm -f $(NAME) $(BONUS)
	@make fclean -C $(LIB_DIR) > /dev/null 2>&1
	@echo "$(BLUE)Project removed.$(NOCOLOR)"
	@echo "$(GREEN)Full clean done.$(NOCOLOR)"

# clean and rebuild the project
re: fclean all

# run the project
run: build
	@./$(NAME)

.PHONY: all clean fclean re run libs build bonus

