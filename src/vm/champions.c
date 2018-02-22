/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:36:45 by jkrause           #+#    #+#             */
/*   Updated: 2018/02/21 21:23:02 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include "vm.h"

#define TMP_BUFFER_SIZE 1024

t_champion			*read_champion(char *filename)
{
	int				fd;
	int				size_read;
	t_string		*str;
	t_champion		*champion;

	fd = open(filename, O_RDONLY);
	str = string_create(MAX_CHAMPION_FILE_SIZE);
	if (!fd)
	{
		ft_dprintf(2, "Cannot open \"%s\" for reading.\n", filename);
		return (0);
	}
	size_read = read(fd, str->buffer, MAX_CHAMPION_FILE_SIZE);
	if (read(fd, str->buffer, MAX_CHAMPION_FILE_SIZE) > 0)
	{
		ft_dprintf(2, "Champion \"%s\" is too big (greater than %ld bytes)\n",
				filename, MAX_CHAMPION_FILE_SIZE);
		return (0);
	}
	champion = (t_champion*)ft_memalloc(sizeof(t_champion));
	champion->file = (t_champion_file*)(void*)str->buffer;
	champion->file_size = size_read;
	string_destroy(str, 0);
	return (champion);
}

/*
** TODO
*/

int					load_champs(void)
{
	return (1);
}
