NAME	= disasm
SRC		= file_op.c instruction.c main.c op.c print.c stdin.c util.c
OBJ		= $(SRC:%.c=%.o)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g
DNAME	= debug
INC		= -I ../ft_printf -I ../libft
LIB		= -L../ft_printf -lftprintf -L../libft -lft

all:	$(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INC) -c $(SRC)
	$(CC) $(CFLAGS) $(LIB) $(OBJ) -o $(NAME)

debug:	fclean
	$(CC) $(DFLAGS) $(INC) -c $(SRC)
	$(CC) $(DFLAGS) $(LIB) $(OBJ) -o $(DNAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME) $(DNAME)

re:		fclean all
