/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 21:03:58 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/11 21:54:07 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_instruction(char *str)
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
