NAME = libft.a
SRC  = ft_split.c ft_strcmp.c ft_strlen_2d.c ft_strlen.c \
		ft_itoa.c ft_strjoin.c
OBJ  = $(SRC:.c=.o)
CC   = gcc
FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(OBJ) libft.h
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: re fclean clean 