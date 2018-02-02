/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 16:58:16 by kyork             #+#    #+#             */
/*   Updated: 2017/06/27 17:39:43 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_VM_H
# define VM_VM_H

# include <stdint.h>


typedef struct			s_player {

	t_array procs; // t_proc*
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

	size_t	proc_id;
	size_t	last_live;
	t_s32	plnum;
	bool	carry;
}						t_proc;

/*
** Find and return the lowest wakeup_at of all live procs.
** @param procs
** @return
*/
size_t					next_cycle_num(t_array procs);

#endif
