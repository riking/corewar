/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:40:47 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/28 02:17:31 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "libftprintf.h"
# include "op.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>

# define BUFF_SIZE 1
# define TAB_SIZE 8
# define COMMENT_TABS 4
# define COMMENT_TAB_CHAR ';'

typedef	struct	s_gn
{
	void		*mem;
	size_t		size;
	int			fd;
	int			eof;
	struct s_gn	*prev;
	struct s_gn	*next;
}				t_gn;

typedef t_gn	t_gnl;

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

typedef	struct	s_in
{
	char		*original;
	char		*label;
	char		*i_name;
	char		*i_oper;
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
	struct s_in	*next;
}				t_in;

typedef t_in	t_instruction;

typedef	struct	s_asm
{
	int			options;
	int			fd;
	int			have_name;
	int			have_comment;
	int			lines;
	int			prog_size;
	char		*filename;
	char		*tmp;
	char		**split;
	t_in		*instruction;
	t_header	header;
	char		body[CHAMP_MAX_SIZE * 2];

}				t_asm;

extern t_op		g_op_tab[17];

void			free_split(char **split);
void			clean_up(t_asm *a);
void			print_error(void);
char			*strip_comments(char *str);
char			*trim_left(char *str);
char			*trim_right(char *str);
int				does_label_exist(t_asm *a, char *str);
int				is_direct_label(char *str);
int				is_indirect_label(char *str);
int				is_label(char *str);
int				count_matching_chars(char *str, char c);
int				count_operands(char *str);
int				betole(int x);
int				chartoint(char *array);
int				check_magic(t_header *header);
int				count_char_array(char **array);
int				get_arg_type(char arg_byte, int arg_number);
int				get_next_line(const int fd, char **line);
int				get_operand_type(char *op);
int				gnl_main(char **memory, t_gnl **gnl, char **line);
int				gnl_more_mem(char **memory, t_gnl **gnl);
int				gnl_read(int fd, t_gnl **gnl, char **memory);
int				gnl_save(char **memory, t_gnl **gnl, char **line);
int				is_direct(char *str);
int				is_indirect(char *str);
int				is_instruction(char *str);
int				is_operand(char *str);
int				is_register(char *str);
int				main(int ac, char **av);
int				put_file_contents
					(char *filename, unsigned char *data, size_t size);
int				show_usage(void);
int				string_is_integer(char *str);
int				string_is_label(char *str);
int				update_acb(int acb, int index, int op_type);
short			chartoshort(char *array);
ssize_t			getfilesize(char *filename);
t_in			*find_label(t_asm *a, char *str);
t_op			find_instruction(char *instruction);
void			*getfilecontents(char *filename, size_t *size);
void			add_instruction_to_queue(t_asm *a, char *name, char *oper);
void			add_label_to_queue(t_asm *a, char *label);
void			destroy_char_array(char **array, int size);
void			generate_output(t_asm *a);
void			generate_hexdump(t_asm *a);
void			get_mandatory_info(t_asm *a);
void			gfc_quit(int errnum, void *memory);
void			header_error(char *msg, t_asm *a);
void			insert_into_char_array(t_asm *a, char *str);
int				is_header_complete(t_asm *a);
void			parse_instructions(t_asm *a);
void			process_instruction(t_asm *a);
void			process_whitespace(char *str);
void			resolve_labels(t_asm *a);
void			routine(t_asm *a);
void			string_prepare(char *line, t_asm *a);
void			string_shift_left(char *str);
void			validate_champion_comment(t_asm *a, int *i);
void			validate_champion_name(t_asm *a, int *i);
void			validate_header_info(t_asm *a);
void			whitespace_consolidate(char *str);
void			whitespace_transform(char *str);
void			whitespace_trim(char *str);
void			warning(char *str);
void			append_nl_string(char **parent, char *child);
int				is_digit(char c);
int				ft_isspace(int c);

#endif
