NAME = cub

CC = cc

CFLAGS =  -Wall -Wextra -Werror -I include

LFLAGS = -Lminilibx-linux/ -lmlx -lX11 -lXext

SRCS = src/rander/randring.c \
	src/main.c


OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft	

LIBFT_A = $(LIBFT_DIR)/libft.a


all: $(NAME) $(LIBFT_A)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) $(LFLAAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: re fclean clean all
