/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:26:19 by kyork             #+#    #+#             */
/*   Updated: 2018/04/11 18:18:52 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_instr.h"

#include <ft_guard.h>
#include <ft_printf.h>

static void			vm_run_proc(t_vm *vm, t_proc *proc)
{
	t_op_func		opfunc;
	size_t			insn_size;

	insn_size = decode_args(vm, proc);
	opfunc = get_op_func(proc->instr[0]);
	opfunc(vm, proc);
	proc->pc = mem_fix(proc->pc + insn_size);
	if (vm_check_redzone(vm))
	{
		ft_dprintf(2, "Memory bounds violation");
		abort();
	}
	guest_read(vm, &proc->instr[0], proc->pc, MAX_INSTR_BYTES);
	vm_set_delay(vm, proc, get_delay(&proc->instr[0]));
}

/*
** NOTE: after calling vm_set_delay(), the proc pointer is bad
*/

static size_t		vm_reset_live_count(t_vm *vm)
{
	size_t			idx;
	size_t			sum;
	t_proc			*proc;

	sum = 0;
	idx = 0;
	while (idx < vm->procs.item_count)
	{
		proc = (t_proc*)ft_ary_get(&vm->procs, idx);
		sum += proc->live_count;
		if (proc->live_count == 0)
		{
			ft_ary_remove(&vm->procs, idx);
		}
		else
		{
			proc->live_count = 0;
			idx++;
		}
	}
	return (sum);
}

static void			vm_die_cycle(t_vm *vm)
{
	size_t			live_count;

	live_count = vm_reset_live_count(vm);
	if (live_count >= NBR_LIVE || vm->no_decrease_checks >= MAX_CHECKS)
	{
		vm->die_cycle_period -= CYCLE_DELTA;
		vm->no_decrease_checks = 0;
	}
	else
		vm->no_decrease_checks++;
	vm->next_die_cycle = vm->cur_cycle + vm->die_cycle_period;
}

void				vm_do_cycle(t_vm *vm)
{
	t_proc			*proc;

	proc = (t_proc*)ft_ary_get(&vm->procs, 0);
	while (vm->cur_cycle == proc->wakeup_at)
	{
		vm_run_proc(vm, proc);
		proc = (t_proc*)ft_ary_get(&vm->procs, 0);
	}
	if (vm->cur_cycle == vm->next_die_cycle)
		vm_die_cycle(vm);
}
