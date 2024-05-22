NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -g
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft/libft.a
GNL		:= ./lib/get_next_line/get_next_line.a

HEADERS	:= -I ./include -I $(LIBMLX)/include 

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    LIBS := $(LIBMLX)/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
else ifeq ($(UNAME_S),Darwin)
    LIBS := $(LIBMLX)/build/libmlx42.a -ldl `pkg-config --libs glfw3` -pthread -lm
endif

SRCS := \
	src/main/main.c \
	src/map/map_border_validator.c \
	src/map/map_color_utils.c \
	src/map/map_initialization_utils.c \
	src/map/map_load_values.c \
	src/map/map_player.c \
	src/map/map_processing_utils.c \
	src/map/map_processing_utils2.c \
	src/map/map_setup.c \
	src/map/map_trim_lines.c \
	src/map/map_validate.c \
	src/movement/key_check.c \
	src/movement/move.c \
	src/raycasting/render_calc.c \
	src/raycasting/render_draw.c \
	src/raycasting/render_horizontal.c \
	src/raycasting/render_ray.c \
	src/raycasting/render_utils.c \
	src/raycasting/render_vertical.c \
	src/utils/error.c \
	src/utils/free.c \
	src/utils/memory.c
OBJS	:= $(SRCS:%.c=objs/%.o)
OBJS_DIR = objs/

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

all: $(LIBMLX)/build/libmlx42.a $(NAME)

$(LIBMLX)/build/libmlx42.a:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT) $(GNL) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)%.o: %.c
	@echo "$(BLUE)Creating $(NAME) object files...$(RESET)"
	mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) all -C ./lib/libft

$(GNL):
	$(MAKE) all -C ./lib/get_next_line

clean:
	$(MAKE) clean -C ./lib/libft
	$(MAKE) clean -C ./lib/get_next_line
	@rm -rf objs
	@rm -rf $(LIBMLX)/build

fclean: clean
	$(MAKE) fclean -C ./lib/libft
	$(MAKE) fclean -C ./lib/get_next_line
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
