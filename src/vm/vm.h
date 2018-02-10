/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 16:58:16 by kyork             #+#    #+#             */
/*   Updated: 2018/02/10 13:43:01 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_VM_H
# define VM_VM_H

# include "../commontypes.h"
# include <libft.h>

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>

# define MAX_INSTR_BYTES 11

typedef struct			s_player {
	t_s32	plnum;
}						t_player;

/*
** regs: element size REG_SIZE, count REG_NUMBER
** pc: program counter, in VM space
** carry: status register
**
** live_count: # of live instructions executed since last check
** wakeup_at: cycle number of next instruction to execute
** proc_id: sequential proc id, for rich debugging
** plnum: player number that spawned this proc, rich debugging
*/
typedef struct			s_proc {
	t_array	regs;
	size_t	pc;
	size_t	live_count;
	size_t	wakeup_at;

	t_u8	instr[MAX_INSTR_BYTES];

	size_t	proc_id;
	size_t	last_live;
	t_s32	plnum;
	bool	carry;
}						t_proc;

/*
** procs: min-heap of t_array<t_proc>
*/
typedef struct			s_vm {
	t_array	procs;
	size_t	cur_cycle;
	size_t	next_die_cycle;
	size_t	die_cycle_period;
	size_t	no_death_checks;

	size_t	pid;

	t_u8	redzone_1[16];
	t_u8	memory[MEM_SIZE];
	t_u8	redzone_2[16];
}						t_vm;

/*
** Set the proc delay for the provided proc, and fix the queue.
** Aborts with a diagnostic if proc is not a member of vm.procs
*/
void					vm_set_delay(t_vm *vm, t_proc *proc, int cycles);
/*
** Create a new proc from the given parent and schedule it.
*/
void					vm_fork_proc(t_vm *vm, t_proc *parent,
							int cycles, int pc_offset);
/*
** Heap percolate functions
*/
bool					vm_fix_down(t_vm *vm, size_t idx);
void					vm_fix_up(t_vm *vm, size_t idx);

/*
** Find and return the lowest wakeup_at of all live procs.
** @param procs
** @return
*/
size_t					vm_next_cycle(t_vm *vm);

bool					vm_do_cycle(t_vm *vm);

void					proc_exec(t_vm *vm, t_proc *proc);

/*
** Returns true if the redzones have been written to (indicates a boundary
** bug).
*/
bool					vm_check_redzone(t_vm *vm);

void					guest_read(t_u8 *buf, size_t ptr, size_t len);
void					guest_write(t_u8 *buf, size_t ptr, size_t len);

#endif
