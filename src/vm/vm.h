/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 16:58:16 by kyork             #+#    #+#             */
/*   Updated: 2018/03/07 14:34:40 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_VM_H
# define VM_VM_H

# include "../commontypes.h"
# include "../instr.h"
# include <libft.h>

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>

# define MAX_INSTR_BYTES 11

typedef struct			s_player {
	size_t	last_live;
	size_t	live_count;
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
	t_u32	regs[REG_NUMBER];
	size_t	pc;
	size_t	live_count;
	size_t	wakeup_at;

	t_u8	instr[MAX_INSTR_BYTES];
	bool	carry;
	t_u32	decoded_arg[3];

	size_t	proc_id;
	size_t	last_live;
	t_s32	plnum;
	bool	last_instr_err;
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

	size_t	pid_next;

	t_array	players;

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
							int cycles, size_t new_pc);
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

void					vm_do_cycle(t_vm *vm);

void					proc_exec(t_vm *vm, t_proc *proc);

/*
** Returns true if the redzones have been written to (indicates a boundary
** bug).
*/
bool					vm_check_redzone(t_vm *vm);

/*
** mem_fix applies circular address space restrictions.
** mem_index applies IDX_MOD restrictions as well as the circular address
** space.
*/
size_t					mem_fix(ssize_t ptr);
size_t					mem_index(size_t base, t_s32 offset);

void					guest_read(t_vm *vm, t_u8 *buf,
							size_t ptr, size_t len);
void					guest_write(t_vm *vm, t_u8 *buf,
							size_t ptr, size_t len);

t_u32					reg_read(t_vm *vm, t_proc *proc, int reg);
void					reg_write(t_vm *vm, t_proc *proc, int reg, t_u32 value);

/*
** Returns the number of bytes the instruction occupies
*/
size_t					decode_args(t_vm *vm, t_proc *proc);

#endif
