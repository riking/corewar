/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 18:31:34 by kyork             #+#    #+#             */
/*   Updated: 2018/04/11 19:12:02 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "../instr.h"
#include <libft.h>
#include <ft_printf.h>

/*
int main(int argc, char **argv)
{
	t_vm_options opts;

	vm_parse_opts(argc, argv);
	if (!opts.ok)
		return 1;
	load_champs();
	if (!true)
		return 1;
	while (opts.live_players > 1)
		vm_run();
	return 0;
}*/

int				print_champion(t_champion *champion)
{
	t_op		op;

	if (HTON32(champion->file->header.magic) != COREWAR_EXEC_MAGIC)
	{
		ft_dprintf(2, "Invalid corewar binary!\n");
		return (-1);
	}
	if ((champion->file_size - sizeof(t_header)) !=
			HTON32(champion->file->header.prog_size))
	{
		ft_dprintf(2, "Size in header does not match!\n");
		return (-1);
	}
	ft_printf("Name: %s\nComment: \"%s\"\n", champion->file->header.prog_name,
			champion->file->header.comment);
	ft_printf("Program size: %d\n", HTON32(champion->file->header.prog_size));
	ft_printf("First operation in binary: ");
	op = g_op_tab[(int)champion->file->instructions[0] - 1];
	ft_printf("%s - %s - %#x(%d)\n", op.name, op.description,
			op.opcode, op.opcode);
	return (0);
}

void			print_area(t_vm *vm)
{
	int			i;
	char		c;

	i = -1;
	while (++i < MEM_SIZE)
	{
		c = vm->memory[i];
		if (c != 0)
			ft_printf("\e[91m%.2x\e[39m ", vm->memory[i]);
		else
			ft_printf("%.2x ", vm->memory[i]);
		if (((i + 1) % 64) == 0)
			ft_printf("\n");
	}
}

int				main(int argc, char **argv)
{
	t_champion	*test;
	t_vm		*vm;

	(void)argc;
	(void)argv;
	vm = (t_vm*)ft_memalloc(sizeof(t_vm));
	ft_bzero(vm->memory, MEM_SIZE);
	if (argc == 2)
	{
		test = read_champion(argv[1]);
		if (test)
		{
			if (print_champion(test) == 0)
			{
				guest_write(vm, (t_u8*)&test->file->instructions,
						1024, HTON32(test->file->header.prog_size));
				print_area(vm);
			}
		}
	}
}
