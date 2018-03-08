/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_jmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:05:34 by kyork             #+#    #+#             */
/*   Updated: 2018/03/07 16:31:23 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_instr.h"

void	op_zjmp(t_vm *vm, t_proc *proc)
{
	t_s32	offset;
	size_t	new_pc;

	offset = (t_s32)proc->decoded_arg[0];
	new_pc = mem_index(proc->pc, offset);
	if (proc->carry)
		proc->pc = new_pc;
}
