/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:36:45 by jkrause           #+#    #+#             */
/*   Updated: 2018/02/21 22:49:49 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include "vm.h"

t_champion			*read_champion(char *filename)
{
	int				fd;
	t_s64			size_read;
	t_string		*str;
	t_champion		*champion;

	fd = open(filename, O_RDONLY);
	str = string_create(MAX_CHAMPION_FILE_SIZE);
	if (!fd)
	{
		ft_dprintf(2, "Cannot open \"%s\" for reading.\n", filename);
		return (0);
	}
	if ((size_read = read(fd, str->buffer, MAX_CHAMPION_FILE_SIZE))
			< (t_s64)sizeof(t_header)
		|| read(fd, str->buffer, MAX_CHAMPION_FILE_SIZE) > 0)
	{
		ft_dprintf(2, "Champion \"%s\" is an invalid file (or is too big).\n",
				filename);
		return (0);
	}
	champion = (t_champion*)ft_memalloc(sizeof(t_champion));
	champion->file = (struct s_champion_file*)(void*)str->buffer;
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
