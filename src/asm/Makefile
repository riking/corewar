NAME	= asm
SRC	= main.c op.c file_op.c stdin.c get_next_line.c whitespace.c util.c
OBJ	= $(SRC:%.c=%.o)
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g
DNAME	= debug
INC	= -I ../ft_printf -I ../libft -I ../../includes/
LIB	= -L../../libft -lftprintf -lft

all:	$(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INC) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

debug:	fclean
	$(CC) $(DFLAGS) $(INC) -c $(SRC)
	$(CC) $(DFLAGS) $(OBJ) $(LIB) -o $(DNAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME) $(DNAME)

re:	fclean all
