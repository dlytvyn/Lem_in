NAME = lem-in
LIBFT = ./libft/libft.a
FT_PRINTF = ./ft_printf/libftprintf.a
GNL = ./GNL/get_next_line.c
CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes

CODE =		./src/main.c\
			./src/additional.c\
			./src/get_link.c\
			./src/get_room.c\
			./src/logic.c\
			./src/matrix.c\
			./src/movement.c\
			./src/parse_data.c\
			./src/search_path.c\

OBJ = $(FDF:.c=.o)

all: $(NAME)

$(NAME):
	cd libft && make && cp libft.a ../
	cd ft_printf && make && cp libftprintf.a ../
	$(CC) $(CFLAGS) $(CODE) $(LIBFT) $(FT_PRINTF) $(GNL) -o $(NAME)
clean:
	cd src && rm -f $(OBJ)
	cd libft && make clean
	cd ft_printf && make clean

fclean: clean
	cd ft_printf && make fclean
	cd libft && make fclean
	/bin/rm -f $(NAME)
	/bin/rm -f colors
	/bin/rm -f libftprintf.a
	/bin/rm -f libft.a

re: fclean all