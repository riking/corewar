/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 12:57:21 by kyork             #+#    #+#             */
/*   Updated: 2018/02/26 15:43:15 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_instr.h"

void		op_and(t_vm *vm, t_proc *proc)
{
	t_u32	result;

	result = proc->decoded_arg[0] & proc->decoded_arg[1];
	reg_write(vm, proc, (int)proc->decoded_arg[2], result);
	proc->carry = result != 0;
}

void		op_xor(t_vm *vm, t_proc *proc)
{
	t_u32	result;

	result = proc->decoded_arg[0] ^ proc->decoded_arg[1];
	reg_write(vm, proc, (int)proc->decoded_arg[2], result);
	proc->carry = result != 0;
}

void		op_or(t_vm *vm, t_proc *proc)
{
	t_u32	result;

	result = proc->decoded_arg[0] | proc->decoded_arg[1];
	reg_write(vm, proc, (int)proc->decoded_arg[2], result);
	proc->carry = result != 0;
}

void		op_add(t_vm *vm, t_proc *proc)
{
	t_u32	result;

	result = proc->decoded_arg[0] + proc->decoded_arg[1];
	reg_write(vm, proc, (int)proc->decoded_arg[2], result);
	proc->carry = result != 0;
}

void		op_sub(t_vm *vm, t_proc *proc)
{
	t_u32	result;

	result = proc->decoded_arg[0] - proc->decoded_arg[1];
	reg_write(vm, proc, (int)proc->decoded_arg[2], result);
	proc->carry = result != 0;
}
