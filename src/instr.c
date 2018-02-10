/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:46:34 by kyork             #+#    #+#             */
/*   Updated: 2018/02/10 14:20:23 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instr.h"

size_t	get_delay(t_u8 *pc)
{
	size_t idx;
	
	idx = 0;
	while (g_op_tab[idx].name)
	{
		if (g_op_tab[idx].opcode == *pc)
		{
			return g_op_tab[idx].cycles;
		}
		idx++;
	}
	return 1;
}
