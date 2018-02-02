# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/19 13:14:58 by kyork             #+#    #+#              #
#    Updated: 2018/01/19 13:14:58 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= corewar

COMMONSRC	+= op.c

ASM_SRC		+= main.c

VM_SRC		+= main.c

ASM_OBJS	= $(addprefix build/, $(COMMONSRC:.c=.o) $(ASM_SRC:.c=.o))
VM_OBJS		= $(addprefix build/, $(COMMONSRC:.c=.o) $(VM_SRC:.c=.o))
LIBS		= libft/libft.a

# Flags start
CFLAGS		+= -Wall -Wextra -Wmissing-prototypes
CFLAGS		+= -I includes/
LDFLAGS		+= -Wall -Wextra

ifndef NO_WERROR
	CFLAGS += -Werror
	LDFLAGS += -Werror
endif

ifdef DEBUG
	CFLAGS += -fsanitize=address -g
	LDFLAGS += -fsanitize=address -g
endif

ifdef RELEASE
	CFLAGS += -O2
	LDFLAGS += -O2
endif
# Flags end

.PHONY: all clean fclean re

all: corewar asm

corewar: $(VM_OBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^

libft/libft.a: libft
	$(MAKE) -C libft libft.a

clean:
	rm -rf build/
	$(MAKE) -C libft clean

fclean: clean
	rm -f corewar asm
	$(MAKE) -C libft fclean

re: fclean
	$(MAKE) all

build:
	mkdir -p build

build/%.o: src/%.c | build
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

