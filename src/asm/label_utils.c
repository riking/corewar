/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:54:41 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/26 23:40:56 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				is_direct_label(char *str)
{
	if ((str[0] == DIRECT_CHAR) && (str[1] == LABEL_CHAR))
		return (1);
	return (0);
}

int				is_indirect_label(char *str)
{
	if (str[0] == LABEL_CHAR)
		return (1);
	return (0);
}

int				is_label(char *str)
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

int				does_label_exist(t_asm *a, char *str)
{
	char			*label;
	t_instruction	*ptr;

	label = str;
	if (is_direct_label(str))
		label = &str[2];
	else if (is_indirect_label(str))
		label = &str[1];
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
	else if (is_indirect_label(str))
		label = &str[1];
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
