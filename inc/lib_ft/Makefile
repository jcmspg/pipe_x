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
SRC_FILES = ft_printf.c\
			ft_aux.c\
			ft_nbrlen.c\
			ft_parse_data.c\
			ft_parse_wrapper.c\
			ft_atoi.c\
			ft_substr.c\
			ft_tolower.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strtrim.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_lstdelone.c\
			ft_lstiter.c\
			ft_lstlast.c\
			ft_lstmap.c\
			ft_lstnew.c\
			ft_lstsize.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar_fd.c\
			ft_toupper.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_split.c\
			ft_strchr.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_isprint.c\
			ft_lstadd_back.c\
			ft_lstadd_front.c\
			ft_lstclear.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_calloc.c\
			ft_bzero.c\
			ft_print_u.c\
			ft_print_xx.c\
			ft_write_nbr.c\
			ft_atol.c\
			ft_print_percent.c\
			ft_write_str.c\
			ft_print_id.c\
			ft_itoa_base.c\
			ft_printf_fd.c\
			ft_strcmp.c\
			ft_itoa.c\
			ft_strdup.c\
			get_next_line_utils.c\
			ft_to_uppers.c\
			ft_write.c\
			ft_print_padding.c\
			get_next_line.c\
			ft_print_type.c\
			ft_print_str.c\
			ft_print_char.c\
			ft_print_ptr.c\

# Convert source files to object files
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

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

