/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:40:47 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/11 06:44:20 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include "libft.h"
# include "libftprintf.h"
# include "op.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

# define BUFF_SIZE 32

typedef	struct		s_gnl
{
	void			*mem;
	size_t			size;
	int				fd;
	int				eof;
	struct s_gnl	*prev;
	struct s_gnl	*next;
}					t_gnl;


typedef struct	s_op
{
	char		*instruction;
	int			arg_count;
	t_arg_type	arg[MAX_ARGS_NUMBER];
	char		opcode;
	int			cycles;
	char		*description;
	int			arg_descript;
	int			short_direct;
}				t_op;

typedef	struct	s_instruction
{
	char		*original;
	char		*label;
	int			type;
	int			opcode;
	int			has_acb;
	int			acb;
	int			short_direct;
	int			arg_count;
	char		**operands;
	int			op_types[MAX_ARGS_NUMBER];
	int			op_values[MAX_ARGS_NUMBER];
	int			size;
	int			address;
	struct s_instruction	*next;
}				t_instruction;

typedef	struct	s_asm
{
	int				fd;
	int				have_name;
	int				valid_name;
	int				have_comment;
	int				valid_comment;
	int				lines;
	int				prog_size;
	char			*filename;
	char			*tmp;
	char			**split;
	t_instruction	*instruction;
	t_header		header;
	char			body[CHAMP_MAX_SIZE * 2];

}				t_asm;


extern t_op		g_op_tab[17];


int		ft_isspace(int c);
void	process_whitespace(char *str);
void	string_shift_left(char *str);
void	whitespace_consolidate(char *str);
void	whitespace_transform(char *str);
void	whitespace_trim(char *str);


int				get_next_line(const int fd, char **line);
char			*stdin_read_eof(size_t *count);
int				put_file_contents
					(char *filename, unsigned char *data, size_t size);
int				bad_input(char *message, char *mem);
int				betole(int	x);
int				chartoint(char *array);
int				check_magic(t_header *header);
int				complex_instruction(char *data, t_op op);
int				get_arg_type(char arg_byte, int arg_number);
int				print_ind(char *data, int index);
int				print_instruction(char	*data, t_op op);
int				print_int_direct(char *data, int index);
int				print_prog_info(t_header *header);
int				print_register(char *data, int index);
int				print_short_direct(char *data, int index);
int				show_usage();
int				main(int ac, char **av);
short			chartoshort(char *array);
ssize_t			getfilesize(char *filename);
void			*getfilecontents(char *filename, size_t *size);
void			quit(int errnum, void *memory);
void			stdin_quit(char *membuf);

#endif
