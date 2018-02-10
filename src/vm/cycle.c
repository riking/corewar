/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:26:19 by kyork             #+#    #+#             */
/*   Updated: 2018/02/10 14:15:29 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_instr.h"

#include <ft_guard.h>
#include <ft_printf.h>

void		vm_do_cycle(t_vm *vm)
{
	t_proc		*proc;
	t_op_func	opfunc;

	proc = (t_proc*)ft_ary_get(&vm->procs, 0);
	opfunc = get_op_func(proc->instr[0]);
	opfunc(vm, proc);
	if (vm_check_redzone(vm))
	{
		ft_dprintf(2, "Memory bounds violation");
		abort();
	}
	guest_read(&proc->instr[0], proc->pc, MAX_INSTR_BYTES);
	vm_set_delay(vm, proc, get_delay(&proc->instr[0]));
}
