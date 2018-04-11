/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_jmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:05:34 by kyork             #+#    #+#             */
/*   Updated: 2018/03/08 13:15:44 by kyork            ###   ########.fr       */
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

#ifdef AFF_REAL_WRITE

void	op_aff(t_vm *vm, t_proc *proc)
{
	int		reg;
	char	ch;

	reg = (int)(unsigned int)proc->decoded_arg[0];
	ch = (char)reg_read(vm, proc, reg);
	write(2, &ch, 1);
}

#else

void	op_aff(t_vm *vm, t_proc *proc)
{
	(void)vm;
	(void)proc;
}

#endif
