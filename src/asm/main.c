/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:11:28 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/11 06:43:16 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		show_usage(void)
{
	ft_printf("usage: ./asm <file.s>\n");
	return (0);
}

char	*trim_left(char	*str)
{
	int	i;
	int	j;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (i)
	{
		if (str[i] == 0)
		{
			str[0] = 0;
			return (str);
		}
		j = 0;
		while (str[i])
		{
			str[j] = str[i];
			j++;
			i++;
		}
		str[j] = 0;
	}
	return (str);
}

char	*trim_right(char *str)
{
	int	i;

	i = (int)ft_strlen(str) - 1;
	while ((i >= 0) && (ft_isspace(str[i])))
	{
		str[i] = 0;
		i--;
	}
	return (str);
}


char	*strip_comments(char *str)
{
	char	*ptr;

	ptr = ft_strchr(str, COMMENT_CHAR);
	if (ptr != NULL)
		ptr[0] = 0;
	ptr = ft_strchr(str, ';');
	if (ptr != NULL)
		ptr[0] = 0;
	return (str);
}

int	count_matching_chars(char *str, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void destroy_char_array(char **array, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (array[i] != NULL)
			free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	header_error(char *msg, t_asm *a)
{
	ft_printf("{red}ERROR:{eoc} %s\n", msg);
	destroy_char_array(a->split, a->lines);
	if (a->tmp != NULL)
		free(a->tmp);
	close(a->fd);
	free(a);
	exit(0);
	return ;
}

void	validate_champion_name(t_asm *a, char *str)
{
	int		len;
	char	*quote1;

	if (a->have_name == 1)
		return (header_error("file has multiple .name commands", a));
	a->have_name = 1;
	if (count_matching_chars(str, '"') != 2)
		return (header_error(".name command not well formatted", a));
	quote1 = ft_strchr(str, '"') + 1;
	len = ft_strchr(quote1, '"') - quote1;
	if (len < 1)
		return (header_error(".name cannot be blank", a));
	if (len > PROG_NAME_LENGTH)
		return (header_error(".name length exceeds PROG_NAME_LENGTH", a));
	ft_strncpy(a->header.prog_name, quote1, len);
//	ft_printf("program name is [%s] ...\n", a->header.prog_name);	//comment out
	a->valid_name = 1;
	return ;
}

void	validate_champion_comment(t_asm *a, char *str)
{
	int		len;
	char	*quote1;

	if (a->have_comment == 1)
		return (header_error("file has multiple .comment commands", a));
	a->have_comment = 1;
	if (count_matching_chars(str, '"') != 2)
		return (header_error(".comment command not well formatted", a));
	quote1 = ft_strchr(str, '"') + 1;
	len = ft_strchr(quote1, '"') - quote1;
	if (len < 1)
		return (header_error(".comment cannot be blank", a));
	if (len > COMMENT_LENGTH)
		return (header_error(".comment length exceeds COMMENT_LENGTH", a));
	ft_strncpy(a->header.comment, quote1, len);
//	ft_printf("program comment is [%s] ...\n", a->header.comment);	//comment out
	a->valid_comment = 1;
	return ;
}

//go through array of strings
//compare each first word to NAME_CMD_STRING and COMMENT_CMD_STRING
//if first non-empty string is other than NAME or COMMENT, throw error
//if multiple results, throw error
//
//make sure command has two quotation marks ("), otherwise error
//make sure length between quotation marks is > 0 and < PROG_NAME_LENGHT and COMMENT_LENGTH
//if not throw error
//save address of first quotation mark + 1  as beginning of string, replace 2nd q mark with 0
//   (or use strncpy)
//   copy into output header


void insert_into_char_array(t_asm *a, char *str)
{
	char	**new_array;
	int		i;

	new_array = ft_memalloc((a->lines + 1) * sizeof(char *));
	i = 0;
	while (i < a->lines)
	{
		new_array[i] = a->split[i];
		i++;
	}
	new_array[i] = str;
	if (a->split != NULL)
		free(a->split);
	a->split = new_array;
	a->lines += 1;
	return ;
}


void	validate_header_info(t_asm *a, char *str)
{
	int	len1;
	int len2;

	len1 = ft_strlen(NAME_CMD_STRING);
	len2 = ft_strlen(COMMENT_CMD_STRING);

	if (ft_strncmp(str, NAME_CMD_STRING, len1) == 0)
		validate_champion_name(a, str);
	else if (ft_strncmp(str, COMMENT_CMD_STRING, len2) == 0)
		validate_champion_comment(a, str);
	else
	{
		ft_printf("{green}%s:%d{eoc} %s\n",
				a->filename, a->lines, a->split[a->lines - 1]);
		return (header_error("expecting .name or .comment command", a));
	}
	return ;
}




void	is_header_complete(t_asm *a)
{
	if (a->have_name == 0)
		header_error("file is missing .name command", a);
	if (a->have_comment == 0)
		header_error("file is missing .comment command", a);
	return ;
}

void	string_prepare(char *line, t_asm *a)
{
	if (a->tmp != NULL)
		free(a->tmp);
	a->tmp = ft_strdup(line);
	a->tmp = strip_comments(a->tmp);
	a->tmp = trim_left(a->tmp);
	a->tmp = trim_right(a->tmp);
	return ;
}

void	get_mandatory_info(t_asm *a)
{
	char *line;
	int	count;

	count = 0;
	while ((get_next_line(a->fd, &line) > 0) && (count < 2))
	{
		insert_into_char_array(a, line);
		if (line != NULL)
		{
			string_prepare(line, a);
			if (a->tmp[0] != 0)
			{
				count += 1;
				validate_header_info(a, a->tmp);
			}
			free(a->tmp);
			a->tmp = NULL;
		}
	}
	is_header_complete(a);
	return ;
}

// if line has 3 words
//   - first word must be label, otherwise error
//   - second word must be instruction, otherwise error
//   - third word must be operands, separated by SEPARATOR_CHAR, otherwise error
// if line has 2 words
//   - first word must be instruction
//   - second word must be operands
// if line has 1 word
//   - must be label
//
// else, error
//

int	is_label(char *str)
{
	int	i;
	int j;

	i = ft_strlen(str) - 1;
	if (str[i] != LABEL_CHAR)
		return (0);
	j = 0;
	while (j < i)
	{
		if ((ft_strchr(LABEL_CHARS, str[j])) == NULL)
			return (0);
		j++;
	}
	return (1);
}

int	is_instruction(char *str)
{
	int i;
	int	tab_size;
	
	i = 0;
	tab_size = sizeof(g_op_tab) / sizeof(t_op);
	while (i < tab_size - 1)
	{
		if (ft_strcmp(str, g_op_tab[i].instruction) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	count_char_array(char **array)
{
	int i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

int	count_operands(char *str)
{
	int		count;
	char	**split;

	if (str == NULL)
		return (0);
	split = ft_strsplit(str, SEPARATOR_CHAR);
	count = count_char_array(split);
	destroy_char_array(split, count);
	return (count);
}

void	add_label_to_queue(t_asm *a, char *label)
{
	t_instruction	*ptr;
	t_instruction	*tail;

	ptr = ft_memalloc(sizeof(t_instruction));
	ptr->type = T_LAB;
	ptr->label = ft_strdup(label);
	ptr->label[ft_strlen(ptr->label) - 1] = 0;
	ptr->original = a->split[a->lines - 1];
	ptr->address = a->prog_size;
	if (a->instruction == NULL)
		a->instruction = ptr;
	else
	{
		tail = a->instruction;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = ptr;
	}
	return ;
}

int		string_is_integer(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			result = 0;
			break ;
		}
		result = 1;
		i++;
	}
	return (result);
}

int		string_is_label(char *str)
{
	int	i;

	if ((str == NULL) || (str[0] == 0))
		return (0);

	i = 0;
	while (str[i])
	{
		if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

int		is_direct(char *str)
{
	if (str[0] != '%')
		return (0);
	if (string_is_integer(&str[1]))
		return (1);
	if ((str[1] == LABEL_CHAR) && (string_is_label(&str[2])))
		return (1);
	return (0);
}

int		is_indirect(char *str)
{
	if (string_is_integer(str))
		return (1);
	return (0);
}

int		is_register(char *str)
{
	int i;

	if (str[0] != 'r')
		return (0);
	i = ft_atoi(&str[1]);
	if ((i >= 1) && (i <= REG_NUMBER))
		return (1);
	return (0);
}

int	get_operand_type(char *op)
{
	if (is_direct(op))
		return (T_DIR);
	if (is_indirect(op))
		return (T_IND);
	if (is_register(op))
		return (T_REG);
	return (0);
}

int		is_operand(char *str)
{
	char	**split;
	char	*s;
	int		i;

	split = ft_strsplit(str, SEPARATOR_CHAR);
	i = 0;
	while (split[i] != NULL)
	{
		s = split[i];
		if ((is_direct(s)) || (is_indirect(s)) || (is_register(s)))
			i++;
		else
		{
			free(split);
			return (0);
		}
	}
	free(split);
	return (1);
}


t_op	find_instruction(char *instruction)
{
	int i;
	int	tab_size;
	
	i = 0;
	tab_size = sizeof(g_op_tab) / sizeof(t_op);
	while (i < tab_size - 1)
	{
		if (ft_strcmp(instruction, g_op_tab[i].instruction) == 0)
			return (g_op_tab[i]);
		i++;
	}
	return (g_op_tab[tab_size]);
}

int		update_acb(int acb, int index, int op_type)
{
	int	tmp;
	int shift;

	tmp = 0;
	shift = 0;
	if (op_type == T_REG)
		tmp = REG_CODE;
	if (op_type == T_DIR)
		tmp = DIR_CODE;
	if (op_type == T_IND)
		tmp = IND_CODE;
	if (index == 0)
		shift = 6;
	if (index == 1)
		shift = 4;
	if (index == 2)
		shift = 2;
	tmp = (tmp << shift);
	return (acb + tmp);
}

void	add_instruction_to_queue(t_asm *a, char *name, char *oper)
{
	t_op			instr;
	t_instruction	*ptr;
	t_instruction	*tail;
	int				i;
	int				type;

	instr = find_instruction(name);
	ptr = ft_memalloc(sizeof(t_instruction));
	ptr->type = T_REG;
	ptr->original = a->split[a->lines - 1];
	ptr->opcode	= instr.opcode;
	ptr->has_acb = instr.arg_descript;
	ptr->address = a->prog_size;

	ptr->operands = ft_strsplit(oper, SEPARATOR_CHAR);
	if (count_char_array(ptr->operands) != instr.arg_count)
		ft_printf("wrong number of operands\n");

	ptr->arg_count = instr.arg_count;
	ptr->short_direct = instr.short_direct;
	ptr->size = 1 + instr.arg_descript;
	i = 0;
	while (i < instr.arg_count)
	{
		type = get_operand_type(ptr->operands[i]);
		if ((instr.arg[i] & type) == 0)
			ft_printf("invalid operand type: %s for instruction %s\n", ptr->operands[i], name);
		ptr->op_types[i] = type;
		if (type == T_REG)
			ptr->size += 1;
		else if ((type == T_IND) || ((type == T_DIR) && (instr.short_direct == 1)))
			ptr->size += 2;
		else if ((type == T_DIR) && (instr.short_direct == 0))
			ptr->size += 4;
		ptr->acb = update_acb(ptr->acb, i, type);
		ptr->op_values[i] = ft_atoi(ptr->operands[i]);
		i++;
	}
	a->prog_size += ptr->size;

	if (a->instruction == NULL)
		a->instruction = ptr;
	else
	{
		tail = a->instruction;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = ptr;
	}
	return ;

	
//
//
//
// implement operands validation
//
//

}

void	process_instruction(t_asm *a)
{
	char	**split;
	int		count;

	split = ft_strsplit(a->tmp, ' ');
	count = count_char_array(split);
	if ((count == 1) || (count == 3))
	{
		if (!is_label(split[0]))
			ft_printf("error: expecting label\n");
		else
			add_label_to_queue(a, split[0]);
	}
	if ((count == 2) || (count == 3))
	{
		if (!is_instruction(split[count - 2]))
			ft_printf("%s\nerror: expecting instruction\n", a->tmp);
		else if (!is_operand(split[count - 1]))
			ft_printf("%s\nerror: expecting operands\n", a->tmp);
		else
			add_instruction_to_queue(a, split[count - 2], split[count - 1]);
	}
	free(split);
}

void	parse_instructions(t_asm *a)
{
	char	*line;

	while (get_next_line(a->fd, &line) > 0)
	{
		insert_into_char_array(a, line);
		if (line != NULL)
		{
			string_prepare(line, a);
			if (a->tmp[0] != 0)
			{
				process_whitespace(a->tmp);
				process_instruction(a);
//				ft_printf("%s\n", a->tmp);
			}
			free(a->tmp);
			a->tmp = NULL;
		}
	}
}


int		is_direct_label(char *str)
{
	if ((str[0] == DIRECT_CHAR) && (str[1] == LABEL_CHAR))
		return (1);
	return (0);
}

int		does_label_exist(t_asm *a, char *str)
{
	char			*label;
	t_instruction	*ptr;

	label = str;
	if (is_direct_label(str))
		label = &str[2];
	ptr = a->instruction;
	while (ptr != NULL)
	{
		if (ptr->type == T_LAB)
		{
			if (ft_strcmp(ptr->label, label) == 0)
				return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

t_instruction	*find_label(t_asm *a, char *str)
{
	char			*label;
	t_instruction	*ptr;

	label = str;
	if (is_direct_label(str))
		label = &str[2];
	ptr = a->instruction;
	while (ptr != NULL)
	{
		if (ptr->type == T_LAB)
		{
			if (ft_strcmp(ptr->label, label) == 0)
				return (ptr);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

void	resolve_labels(t_asm *a)
{
	t_instruction	*ptr;
	t_instruction	*label;
	int				i;
	
	ptr = a->instruction;
	while (ptr != NULL)
	{
		if (ptr->type == T_REG)
		{
			i = 0;
			while (i < ptr->arg_count)
			{
				if (is_direct_label(ptr->operands[i]))
				{
					label = find_label(a, ptr->operands[i]);
					if (label == NULL)
						ft_printf("error: label not found '%s'\n", ptr->operands[i]);
					else
						ptr->op_values[i] = label->address - ptr->address;
				}
				else if (is_register(ptr->operands[i]))
					ptr->op_values[i] = ft_atoi(&ptr->operands[i][1]);
				else if (is_indirect(ptr->operands[i]))
					ptr->op_values[i] = ft_atoi(ptr->operands[i]);
				else if (is_direct(ptr->operands[i]))
					ptr->op_values[i] = ft_atoi(&ptr->operands[i][1]);
				i++;
			}
		}
		ptr = ptr->next;
	}
}

void	generate_output(t_asm *a)
{
	int				i;
	int				j;
	t_instruction	*ptr;

	a->header.magic = betole(COREWAR_EXEC_MAGIC);
	a->header.prog_size = betole(a->prog_size);
	ptr = a->instruction;
	i = 0;
	while (ptr)
	{
		if (ptr->type == T_REG)
		{
			a->body[i++] = (char)ptr->opcode;
			if (ptr->has_acb)
				a->body[i++] = (char)ptr->acb;
			j = 0;
			while (j < ptr->arg_count)
			{
				if (ptr->op_types[j] == T_REG)
					a->body[i++] = (char)ptr->op_values[j];
				if ((ptr->op_types[j] == T_IND) || ((ptr->op_types[j] == T_DIR) && (ptr->short_direct == 1)))
				{
					a->body[i++] = (char)(ptr->op_values[j] >> 8);
					a->body[i++] = (char)ptr->op_values[j];
				}
				if ((ptr->op_types[j] == T_DIR) && (ptr->short_direct == 0))
				{
					a->body[i++] = (char)(ptr->op_values[j] >> 24);
					a->body[i++] = (char)(ptr->op_values[j] >> 16);
					a->body[i++] = (char)(ptr->op_values[j] >> 8);
					a->body[i++] = (char)ptr->op_values[j];
				}
				j++;
			}
		}
		ptr = ptr->next;
	}
}

void	routine(t_asm *a)
{
	get_mandatory_info(a);
	parse_instructions(a);
	resolve_labels(a);
	ft_printf("prog size: %d\n", a->prog_size);
	if (a->prog_size > CHAMP_MAX_SIZE)
		ft_printf("error: prog size exceeds CHAMP_MAX_SIZE\n");
	generate_output(a);
	//
	//destroy instruction linked list
	//
	put_file_contents("assembler.output", (unsigned char *)&a->header, sizeof(t_header) + a->prog_size);


	destroy_char_array(a->split, a->lines);
	free(a);
}

int		main(int ac, char **av)
{
	int		fd;
	t_asm	*a;

	if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) != -1)
		{
			a = ft_memalloc(sizeof(t_asm));
			a->fd = fd;
			a->filename = av[1];
			routine(a);
			close(fd);
			return (0);
		}
		else
		{
			ft_printf("{red}ERROR:{eoc} %s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	else
		return (show_usage());
	return (0);
}

// assembler logic:
//
// -get raw input
// -use ft_strsplit, split by newlines '\n', trim ' ' and '\t' from beginning and end of string,
// replace all '\t' with ' '; replace multiple ' ' with a single ' ';
// -scan for NAME_CMD_STRING and COMMENT_CMD_STRING, save values between (") quotation marks
// -use a struct and assign each line a line number (original line number)
// -remove NULL's from strsplit array (multiple empty lines)
// -iterate through each line and remove everything after first COMMENT_CHAR #
// -trim each string from left side and right side
// -iterate through the array, if last character of first word ends with LABEL_CHAR :, 
// make sure the rest of the characters confirm to "LABEL_CHARS" otherwise error
// 
// add label to an array of labels for next valid instruction
// 
// one command can have multiple labels?
// make sure there is no duplicate labels
// <-- at this point we should have only relevant code
//
// compare first leftmost word of each line with known instruction array,
// if instruction is unknown throw an error,
// assign an opcode for each instruction in the struct;
// replace the instruction with blank spaces
// remove all whitespace
// <-- at this point we should only have operands and separators
// 
// use ft_strsplit on each line again, split by SEPARATOR_CHAR
// identify each operand: must be either T_REG, T_DIR, T_IND or otherwise error
// zaz's assembler supports registers r0 through r99
//
//
// //
// <--- if
//
//
