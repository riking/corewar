/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:46:57 by kyork             #+#    #+#             */
/*   Updated: 2018/03/07 14:34:24 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_instr.h"

void	op_fork(t_vm *vm, t_proc *proc) {
	t_s32	offset;
	size_t	dest;

	offset = ((t_s32)proc->decoded_arg[0]) % IDX_MOD;
	dest = mem_index(proc->pc, offset);
	vm_fork_proc(vm, proc, 800, dest);
}

void	op_lfork(t_vm *vm, t_proc *proc) {
	t_s32	offset;
	size_t	dest;

	offset = (t_s32)proc->decoded_arg[0];
	dest = mem_index(proc->pc, offset);
	vm_fork_proc(vm, proc, 1000, dest);
}

void	op_live(t_vm *vm, t_proc *proc) {
	size_t	idx;

	proc->live_count++;
	proc->last_live = vm->cur_cycle;
	idx = 0;
	while (idx < vm->players.item_count) {
		if (((t_player*)ft_ary_get(&vm->players, idx))->plnum ==
				(t_s32)proc->decoded_arg[0]) {
			((t_player*)ft_ary_get(&vm->players, idx))->last_live =
				vm->cur_cycle;
			((t_player*)ft_ary_get(&vm->players, idx))->live_count++;
		}
		idx++;
	}
}
