NAME = cub3D
CC = cc
CFLAGS = -I include -Wall -Wextra -Werror

SRCS_PARSING = src/main.c \
			src/parsing/parse.c\
src/parsing/parse_configurations.c\
src/parsing/parse_colors.c\
src/parsing/parse_textures.c\
src/parsing/parse_map.c \
			src/parsing/parse_objects.c\
src/parsing/parsing_utils.c\
src/parsing/validate_map.c\
src/parsing/validate_map_utils.c\
libraries/get_line/get_line.c\
libraries/get_line/get_line_utils.c

SRC_RANDRING = src/rander/randring.c\
src/rander/draw.c\
src/rander/render_objects.c\
src/rander/player_movment.c\
src/rander/ddaAlgo.c\
src/rander/handle_key.c\
src/rander/load_textures.c\
src/rander/drwa_utils.c\
src/rander/camera_plan.c

SRC_GAMEPLAY = src/gameplay/objects.c\
src/gameplay/combat.c\
src/gameplay/enemies.c\
src/gameplay/health_system.c\
src/gameplay/hud.c\
src/gameplay/minimap.c\
src/gameplay/progression.c\
src/gameplay/level_manager.c\
src/gameplay/replayability.c

SRC_EFFECTS = src/effects/impact.c\
src/effects/camera.c\
src/effects/ui.c

SRC_AUDIO = src/audio/audio.c

SRC_VISUAL = src/visual_polish/visual_effects.c

SRC_UI = src/ui/menu.c

SRCS = $(SRCS_PARSING) $(SRC_RANDRING) $(SRC_GAMEPLAY) $(SRC_EFFECTS) $(SRC_AUDIO) $(SRC_VISUAL) $(SRC_UI)
SRCS += src/enemy/ai_behaviors.c
OBJ = ${SRCS:.c=.o}

LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = /usr/include/minilibx-linux

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -L $(LIBFT_DIR) -L$(MLX_DIR) -lmlx -lft -lm -lXext -lX11 -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

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
