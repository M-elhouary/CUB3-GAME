NAME = cub3D_bonus
CC = cc
CFLAGS = -I includes
SRCS_PARSING = src/main.c \
			src/parsing/parse.c\
			src/parsing/parse_config_utils.c\
			src/parsing/parse_color_and_texture.c\
			src/parsing/parse_map.c \
			src/parsing/parsing_utils.c\
			src/parsing/validate_map.c\
			src/parsing/validate_map_utils.c\
			libraries/get_line/get_line.c\
			libraries/get_line/get_line_utils.c\


SRC_RANDRING = src/rander/randring.c\
				src/rander/draw.c\
				src/rander/player_movment.c\
				src/rander/player_movment_utils.c\
				src/rander/raycasting.c\
				src/rander/mini_map.c\
				src/rander/mini_map_utils.c\
				src/rander/handle_key.c\
				src/rander/load_textures.c\
				src/rander/draw_utils.c\
				src/rander/camera_plan.c\

SRCS = $(SRCS_PARSING)  $(SRC_RANDRING)

OBJ = ${SRCS:.c=.o}

LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = /usr/include/minilibx-linux

all: $(NAME)

$(NAME): $(LIBFT)  $(OBJ)
	$(CC) $(OBJ) -L $(LIBFT_DIR) -L$(MLX_DIR) -lmlx -lft -lm -lXext -lX11  -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
