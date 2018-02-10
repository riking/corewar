/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 18:31:34 by kyork             #+#    #+#             */
/*   Updated: 2018/02/10 14:00:38 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
}
