/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 09:46:29 by kyork             #+#    #+#             */
/*   Updated: 2018/02/27 11:10:27 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_instr.h"
#include "../instr.h"

void				op_ld(t_vm *vm, t_proc *proc) {
	t_u32	value;
	t_s32	offset;
	size_t	addr;

	if (acb_get(proc->instr[1], 0) == DIR_CODE)
		value = (t_s32)proc->decoded_arg[0];
	else if (acb_get(proc->instr[1], 0) == IND_CODE)
	{
		offset = (t_s32)proc->decoded_arg[0];
		addr = mem_index(proc->pc, offset % IDX_MOD);
		guest_read(vm, (t_u8*)&value, addr, REG_SIZE);
	}
	reg_write(vm, proc, (int)proc->decoded_arg[1], value);
	proc->carry = value != 0;
}

void				op_lld(t_vm *vm, t_proc *proc) {
	t_u32	value;
	t_s32	offset;
	size_t	addr;

	if (acb_get(proc->instr[1], 0) == DIR_CODE)
		value = (t_s32)proc->decoded_arg[0];
	else if (acb_get(proc->instr[1], 0) == IND_CODE)
	{
		offset = (t_s32)proc->decoded_arg[0];
		addr = mem_index(proc->pc, offset);
		guest_read(vm, (t_u8*)&value, addr, REG_SIZE);
	}
	reg_write(vm, proc, (int)proc->decoded_arg[1], value);
	proc->carry = value != 0;
}

void				op_st(t_vm *vm, t_proc *proc) {
	t_u32	value;
	t_s32	offset;
	size_t	addr;

	value = reg_read(vm, proc, (int)proc->decoded_arg[0]);
	if (acb_get(proc->instr[1], 1) == REG_CODE)
	{
		reg_write(vm, proc, (int)proc->decoded_arg[1], value);
	}
	else if (acb_get(proc->instr[1], 1) == IND_CODE)
	{
		offset = (t_s32)proc->decoded_arg[1];
		addr = mem_index(proc->pc, offset % IDX_MOD);
		guest_write(vm, (t_u8*)&value, addr, REG_SIZE);
	}
	proc->carry = value != 0;
}
