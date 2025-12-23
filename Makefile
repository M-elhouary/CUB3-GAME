NAME = cub3D
BONUS = cub3D_bonus
CC = cc
CFLAGS = -I include
SRCS_PARSING = src/main.c \
			src/parsing/parse.c\
			src/parsing/parse_configurations.c\
			src/parsing/parse_colors.c\
			src/parsing/parse_textures.c\
			src/parsing/parse_map.c \
			src/parsing/parsing_utils.c\
			src/parsing/validate_map.c\
			src/parsing/validate_map_utils.c\
			libraries/get_line/get_line.c\
			libraries/get_line/get_line_utils.c\


SRC_RANDRING = src/rander/randring.c\
				src/rander/draw.c\
				src/rander/player_movment.c\
				src/rander/ddaAlgo.c\
				src/rander/handle_key.c\
				src/rander/load_textures.c\
				src/rander/drwa_utils.c\
				src/rander/camera_plan.c\


SRCS_PARSING_BONUS = src/main_bonus.c \
			src/parsing_bonus/parse_bonus.c\
			src/parsing_bonus/parse_configurations_bonus.c\
			src/parsing_bonus/parse_colors_bonus.c\
			src/parsing_bonus/parse_textures_bonus.c\
			src/parsing_bonus/parse_map_bonus.c \
			src/parsing_bonus/parsing_utils_bonus.c\
			src/parsing_bonus/validate_map_bonus.c\
			src/parsing_bonus/validate_map_utils_bonus.c\
			libraries/get_line/get_line.c\
			libraries/get_line/get_line_utils.c\


SRC_RANDRING_BONUS = src/rander_bonus/draw_bonus.c\
				src/rander_bonus/player_movment_bonus.c\
				src/rander_bonus/player_movment_utils_bonus.c\
				src/rander_bonus/raycasting_bonus.c\
				src/rander_bonus/randring_bonus.c\
				src/rander_bonus/mini_map_bonus.c\
				src/rander_bonus/mini_map_utils_bonus.c\
				src/rander_bonus/handle_key_bonus.c\
				src/rander_bonus/load_textures_bonus.c\
				src/rander_bonus/draw_utils_bonus.c\
				src/rander_bonus/camera_plan_bonus.c\



SRCS = $(SRCS_PARSING)  $(SRC_RANDRING)
SRCS_BONUS = $(SRCS_PARSING_BONUS)  $(SRC_RANDRING_BONUS)

OBJ = ${SRCS:.c=.o}
OBJ_BONUS = ${SRCS_BONUS:.c=.o}

LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = /usr/include/minilibx-linux

all: $(NAME)

$(NAME): $(LIBFT)  $(OBJ)
	$(CC) $(OBJ) -L $(LIBFT_DIR) -L$(MLX_DIR) -lmlx -lft -lm -lXext -lX11  -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(LIBFT)  $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) -L $(LIBFT_DIR) -L$(MLX_DIR) -lmlx -lft -lm -lXext -lX11  -o $(BONUS)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean bonus fclean re
