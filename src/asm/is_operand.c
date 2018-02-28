/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:47:01 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/26 23:15:07 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	if ((str[0] == LABEL_CHAR) && (string_is_label(&str[1])))
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

int		get_operand_type(char *op)
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
			free_split(split);
			return (0);
		}
	}
	free_split(split);
	return (1);
}
