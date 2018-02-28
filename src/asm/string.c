/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:50:27 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/11 21:53:23 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
		if (!is_digit(str[i]))
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
