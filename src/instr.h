/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:16:12 by kyork             #+#    #+#             */
/*   Updated: 2018/02/10 13:59:56 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "commontypes.h"

typedef struct	s_op
{
	char		*instruction;
	int			arg_count;
	t_arg_type	arg[MAX_ARGS_NUMBER];
	char		opcode;
	int			cycles;
	char		*description;
	int			arg_descript;
	int			short_direct;
}				t_op;

extern t_op		g_op_tab[17];

typedef struct		s_decoded {
	t_u8		opcode;
	t_u8		acb;
	t_u32		arg[4];
}					t_decoded;

/*
** Returns REG_CODE, DIR_CODE, or IND_CODE (or 0 if no ACB entry).
*/
int			acb_get(t_u8 acb, int idx);

size_t		get_delay(t_u8 *pc);

/*
** Largest instruction:
** and dir,dir,reg
** sti reg, dir, dir
** lldi dir, dir, reg
** [14] [ACB] [0 0 0 0] [0 0 0 0] [1]
** 1 + 1 + 8 + 1 = 11 bytes
*/
