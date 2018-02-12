/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:10:47 by kyork             #+#    #+#             */
/*   Updated: 2018/02/12 15:22:01 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "../instr.h"
#include "vm_instr.h"

static size_t	decode_sdirect(t_vm *vm, t_proc *proc, t_insndec *state)
{
	t_s16	short_v;
	t_u32	full_v;

	(void)vm;
	if (state->opd->short_direct)
	{
		ft_memcpy(&short_v, proc->instr + state->by_offset, sizeof(t_s16));
		full_v = (t_s32)short_v;
		proc->decoded_arg[state->argn] = full_v;
		state->by_offset += 2;
		return 2;
	}
	else
	{
		ft_memcpy(&full_v, proc->instr + state->by_offset, DIR_SIZE);
		proc->decoded_arg[state->argn] = full_v;
		state->by_offset += 4;
		return 4;
	}
}

static void		decode_reg(t_vm *vm, t_proc *proc, t_insndec *state)
{
	t_u8	regn;

	(void)vm;
	regn = proc->instr[state->by_offset];
	state->by_offset++;
	if (regn == 0 || regn > REG_NUMBER)
		proc->decoded_arg[state->argn] = 0;
	else
		proc->decoded_arg[state->argn] = regn;
}

static void		decode_ind(t_vm *vm, t_proc *proc, t_insndec *state)
{
	t_s16	pcoff;
	t_u32	full_v;

	(void)vm;
	ft_memcpy(&pcoff, proc->instr + state->by_offset, IND_SIZE);
	full_v = (t_s32)pcoff;
	state->by_offset += 2;
	proc->decoded_arg[state->argn] = full_v;
}

/*
** returns false if last_instr_err should be set
*/
size_t			decode_args(t_vm *vm, t_proc *proc)
{
	t_insndec	state;
	t_u8		acb;

	ft_memset(&proc->decoded_arg[0], 0, sizeof(t_u32) * 3);
	if (!(proc->instr[0] > 0 && proc->instr[0] <= 0x10))
		return 1;
	state = (t_insndec){&g_op_tab[proc->instr[0] - 1], 1, 0};
	if (!state.opd->needs_acb)
		return 1 + decode_sdirect(vm, proc, &state);
	acb = proc->instr[++state.by_offset];
	while (state.argn < state.opd->arg_count)
	{
		if (acb_get(acb, state.opd->arg_count) == REG_CODE)
			decode_reg(vm, proc, &state);
		else if (acb_get(acb, state.opd->arg_count) == IND_CODE)
			decode_ind(vm, proc, &state);
		else if (acb_get(acb, state.opd->arg_count) == DIR_CODE)
			decode_sdirect(vm, proc, &state);
		else
			state.by_offset += 1;
		state.argn++;
	}
	return state.by_offset;
}

