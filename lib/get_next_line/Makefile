NAME = get_next_line.a

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
OBJS_DIR = ../../objs/get_next_line/

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

SRCS = \
	get_next_line.c \
	get_next_line_utils.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_BONUS)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	@ar rc $(NAME) $(OBJS) $(OBJS_BONUS)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)%.o: %.c
	@echo "$(BLUE)Creating $(NAME) object files...$(RESET)"
	mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning $(NAME) object files...$(RESET)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME) executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
