/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 01:33:57 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/28 02:16:52 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_digit(char c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

int		ft_isspace(int c)
{
	if ((c >= 0x09) && (c <= 0x0d))
		return (1);
	else if (c == 0x20)
		return (1);
	else
		return (0);
}

int		is_header_complete(t_asm *a)
{
	if ((a->have_name == 1) && (a->have_comment == 1))
		return (1);
	return (0);
}

void	warning(char *str)
{
	ft_printf("{yellow}WARNING:{eoc} %s\n", str);
	return ;
}

void	append_nl_string(char **parent, char *child)
{
	char	*tmp;
	int		len;

	len = ft_strlen(*parent) + ft_strlen(child);
	tmp = ft_memalloc(len + 3);
	ft_strcpy(tmp, *parent);
	ft_strcpy(&tmp[ft_strlen(*parent)], "\n");
	ft_strcpy(&tmp[ft_strlen(*parent) + 1], child);
	free(*parent);
	*parent = tmp;
	return ;
}
