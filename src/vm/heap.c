/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 10:48:57 by kyork             #+#    #+#             */
/*   Updated: 2018/02/10 14:09:23 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ft_printf.h>

#define HEAP_PARENT(n) ((n-1)/2)
#define HEAP_LCHILD(n) (n*2+1)
#define HEAP_RCHILD(n) (n*2+2)

#define OVERFLOW 0x7FFFFFFF

static bool	proc_sooner(t_vm *vm, size_t idx1, size_t idx2)
{
	t_proc *p1;
	t_proc *p2;

	p1 = (t_proc*)ft_ary_get(&vm->procs, idx1);
	p2 = (t_proc*)ft_ary_get(&vm->procs, idx2);
	if (p1->wakeup_at < p2->wakeup_at)
		return true;
	if (p1->wakeup_at > p2->wakeup_at)
		return false;
	return p1->proc_id < p2->proc_id;
}

bool		vm_fix_down(t_vm *vm, size_t idx0)
{
	size_t	idx;
	size_t	ch1;
	size_t	ch2;

	idx = idx0;
	while (1)
	{
		ch1 = HEAP_LCHILD(idx);
		if (ch1 >= vm->procs.item_count || ch1 > OVERFLOW)
			break;
		ch2 = HEAP_RCHILD(idx);
		if ((ch2 < vm->procs.item_count) && proc_sooner(vm, ch2, ch1))
			ch1 = ch2;
		if (!proc_sooner(vm, ch1, idx))
			break;
		ft_ary_swap(&vm->procs, ch1, idx);
		idx = ch1;
	}
	return idx > idx0;
}

void		vm_fix_up(t_vm *vm, size_t idx)
{
	size_t	parent;

	while (1)
	{
		if (idx == 0)
			break;
		parent = HEAP_PARENT(idx);
		if (!proc_sooner(vm, idx, parent))
			break;
		ft_ary_swap(&vm->procs, parent, idx);
		idx = parent;
	}
}

void		vm_set_delay(t_vm *vm, t_proc *proc, int cycles)
{
	t_proc	**ary;
	ssize_t	idx;

	ary = (t_proc**)vm->procs.ptr;
	idx = (proc - ary[0]);
	if (idx < 0 || idx > (ssize_t)vm->procs.item_count)
	{
		ft_dprintf(2, "Error: proc pointer %p is not member of proc array %p"
				" (len %zd)", proc, ary, vm->procs.item_count);
		abort();
	}
	proc->wakeup_at = vm->cur_cycle + cycles;
	if (!vm_fix_down(vm, idx)) {
		vm_fix_up(vm, idx);
	}
}

