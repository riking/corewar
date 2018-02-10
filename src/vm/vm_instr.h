/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:10:57 by kyork             #+#    #+#             */
/*   Updated: 2018/02/10 14:14:39 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_VM_INSTR_H
# define VM_VM_INSTR_H

typedef void		(*t_op_func)(t_vm *vm, t_proc *proc);

t_op_func			get_op_func(t_u8 opcode);

void				op_live(t_vm *vm, t_proc *proc);
void				op_ld(t_vm *vm, t_proc *proc);
void				op_st(t_vm *vm, t_proc *proc);
void				op_add(t_vm *vm, t_proc *proc);
void				op_sub(t_vm *vm, t_proc *proc);
void				op_and(t_vm *vm, t_proc *proc);
void				op_or(t_vm *vm, t_proc *proc);
void				op_xor(t_vm *vm, t_proc *proc);
void				op_zjmp(t_vm *vm, t_proc *proc);
void				op_ldi(t_vm *vm, t_proc *proc);
void				op_stu(t_vm *vm, t_proc *proc);
void				op_fork(t_vm *vm, t_proc *proc);
void				op_lld(t_vm *vm, t_proc *proc);
void				op_lldi(t_vm *vm, t_proc *proc);
void				op_lfork(t_vm *vm, t_proc *proc);
void				op_aff(t_vm *vm, t_proc *proc);
void				op_other(t_vm *vm, t_proc *proc);

#endif
