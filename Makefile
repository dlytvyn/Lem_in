NAME = lem-in
FT_PRINTF = libftprintf.a
CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes

CODE =		./src/main.c\
			./src/add_2.c\
			./src/additional.c\
			./src/get_link.c\
			./src/get_room.c\
			./src/get_room_add.c\
			./src/logic.c\
			./src/logic_add.c\
			./src/matrix.c\
			./src/movement.c\
			./src/movement_add.c\
			./src/parse_data.c\
			./src/search_path.c\
			./src/search_path_add.c\
			./src/search_path_add2.c\

OBJ = $(CODE:.c=.o)

all: $(NAME)

$(NAME):
	cd ft_printf && make && cp libftprintf.a ../
	$(CC) $(CFLAGS) $(CODE) $(FT_PRINTF) -o $(NAME)
clean:
	cd src && rm -f $(OBJ)
	cd ft_printf && make clean

fclean: clean
	cd ft_printf && make fclean
	/bin/rm -f $(NAME)
	/bin/rm -f colors
	/bin/rm -f libftprintf.a

re: fclean all