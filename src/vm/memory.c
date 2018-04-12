/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 19:01:10 by jkrause           #+#    #+#             */
/*   Updated: 2018/04/11 20:10:35 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** TODO: Proper error handling?
** TODO: Determine if the guest_read/write functions should be combined.
** TODO: Should it handle wraparound (call mem_fix)?
*/

void					guest_read(t_vm *vm, t_u8 *buf,
							size_t ptr, size_t len)
{
	ft_memcpy(buf, vm->memory + ptr, len);
}

void					guest_write(t_vm *vm, t_u8 *buf,
							size_t ptr, size_t len)
{
	ft_memcpy(vm->memory + ptr, buf, len);
}

/*
** TODO: Do we need the vm instance in these two functions?
*/

t_u32					reg_read(t_vm *vm, t_proc *proc, int reg)
{
	(void)vm;
	return (proc->regs[reg]);
}

void					reg_write(t_vm *vm, t_proc *proc, int reg,
							t_u32 value)
{
	(void)vm;
	proc->regs[reg] = value;
}
