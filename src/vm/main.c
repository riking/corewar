/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 18:31:34 by kyork             #+#    #+#             */
/*   Updated: 2018/02/21 21:28:35 by jkrause          ###   ########.fr       */
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

void			print_champion(t_champion *champion)
{
	t_op		op;

	if (HTON32(champion->file->header.magic) != COREWAR_EXEC_MAGIC)
	{
		ft_dprintf(2, "Invalid corewar binary!\n");
		return ;
	}
	ft_printf("Name: %s\nComment: \"%s\"\n", champion->file->header.prog_name,
			champion->file->header.comment);
	ft_printf("Program size: %d", HTON32(champion->file->header.prog_size));
	if ((champion->file_size - sizeof(t_header)) !=
			HTON32(champion->file->header.prog_size))
		ft_printf(" - Invalid size!\n");
	else
		ft_printf(" - Valid\n");
	ft_printf("First operation in binary: ");
	op = g_op_tab[(int)champion->file->full.instructions[0] - 1];
	ft_printf("%s - %s - %#x(%d)\n", op.name, op.description,
			op.opcode, op.opcode);
}

int				main(int argc, char **argv)
{
	t_champion *test;

	(void)argc;
	(void)argv;
	if (argc == 2)
	{
		test = read_champion(argv[1]);
		if (test)
			print_champion(test);
	}
}
