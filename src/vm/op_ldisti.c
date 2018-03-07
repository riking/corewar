/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 09:46:29 by kyork             #+#    #+#             */
/*   Updated: 2018/02/27 11:28:03 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_instr.h"
#include "../instr.h"

void				op_ldi(t_vm *vm, t_proc *proc)
{
	t_u32	value;
	t_u32	addr1;
	size_t	addr;

	if (acb_get(proc->instr[1], 0) == DIR_CODE)
		addr1 = proc->decoded_arg[0];
	else if (acb_get(proc->instr[1], 0) == IND_CODE)
		addr1 = mem_index(proc->pc, ((t_s16)proc->decoded_arg[0]) % IDX_MOD);
	else if (acb_get(proc->instr[1], 0) == REG_CODE)
		addr1 = reg_read(vm, proc, (int)proc->decoded_arg[0]);
	else
		return;
	if (acb_get(proc->instr[1], 1) == DIR_CODE)
		addr1 += proc->decoded_arg[1];
	else if (acb_get(proc->instr[1], 1) == REG_CODE)
		addr1 += reg_read(vm, proc, (int)proc->decoded_arg[1]);
	addr = mem_fix((ssize_t)(t_s32)addr1);
	guest_read(vm, (t_u8*)&value, addr, REG_SIZE);
	reg_write(vm, proc, (int)proc->decoded_arg[2], value);
	proc->carry = value != 0;
}

void				op_lldi(t_vm *vm, t_proc *proc)
{
	t_u32	value;
	t_u32	addr1;
	size_t	addr;

	if (acb_get(proc->instr[1], 0) == DIR_CODE)
		addr1 = proc->decoded_arg[0];
	else if (acb_get(proc->instr[1], 0) == IND_CODE)
		addr1 = mem_index(proc->pc, (t_s16)proc->decoded_arg[0]);
	else if (acb_get(proc->instr[1], 0) == REG_CODE)
		addr1 = reg_read(vm, proc, (int)proc->decoded_arg[0]);
	else
		return;
	if (acb_get(proc->instr[1], 1) == DIR_CODE)
		addr1 += proc->decoded_arg[1];
	else if (acb_get(proc->instr[1], 1) == REG_CODE)
		addr1 += reg_read(vm, proc, (int)proc->decoded_arg[1]);
	addr = mem_fix((ssize_t)(t_s32)addr1);
	guest_read(vm, (t_u8*)&value, addr, REG_SIZE);
	reg_write(vm, proc, (int)proc->decoded_arg[2], value);
	proc->carry = value != 0;
}

void				op_sti(t_vm *vm, t_proc *proc)
{
	t_u32	value;
	t_u32	addr1;
	size_t	addr;

	value = reg_read(vm, proc, (int)proc->decoded_arg[0]);
	if (acb_get(proc->instr[1], 1) == DIR_CODE)
		addr1 = proc->decoded_arg[1];
	else if (acb_get(proc->instr[1], 1) == IND_CODE)
		addr1 = mem_index(proc->pc, ((t_s16)proc->decoded_arg[1]) % IDX_MOD);
	else if (acb_get(proc->instr[1], 1) == REG_CODE)
		addr1 = reg_read(vm, proc, (int)proc->decoded_arg[1]);
	else
		return;
	if (acb_get(proc->instr[1], 2) == DIR_CODE)
		addr1 += proc->decoded_arg[2];
	else if (acb_get(proc->instr[1], 2) == REG_CODE)
		addr1 += reg_read(vm, proc, (int)proc->decoded_arg[2]);
	addr = mem_fix((ssize_t)(t_s32)addr1);
	guest_write(vm, (t_u8*)&value, addr, REG_SIZE);
	proc->carry = value != 0;
}
