NAME = cub3D
CC = cc
CFLAGS = -I include
SRC = 	src/main.c src/parsing/parse.c src/parsing/parse_color_and_texture.c  src/parsing/parse_map.c \
		libraries/get_next_line/get_next_line.c libraries/get_next_line/get_next_line_utils.c\
		
OBJ = ${SRC:.c=.o}
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = /usr/include/minilibx-linux

all: $(NAME)

$(NAME): $(LIBFT)  $(OBJ)
	$(CC) $(OBJ) -L$(LIBFT_DIR) -L$(MLX_DIR) -lmlx -lft -lXext -lX11  -o $(NAME)

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
