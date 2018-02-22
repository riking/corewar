/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:36:38 by jkrause           #+#    #+#             */
/*   Updated: 2018/02/21 21:42:29 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Rudimentary length-tagged string library
** This is mostly untested territory, and used for champion file reading.
*/

#include "commontypes.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

t_string			*string_create(t_u64 length)
{
	t_string		*string;

	string = (t_string*)ft_memalloc(sizeof(t_string));
	string->buffer = (char*)ft_memalloc(length);
	string->length = length;
	return (string);
}

t_string			*string_wrap(char *buffer, t_u64 length)
{
	t_string		*string;

	string = string_create(length);
	ft_memcpy(string->buffer, buffer, length);
	return (string);
}

void				string_append(t_string *src, t_string *append)
{
	t_string		*new;

	if (!src || !append)
		return ;
	new = string_create(src->length + append->length);
	ft_memcpy(new->buffer, src->buffer, src->length);
	ft_memcpy(new->buffer, append->buffer, append->length);
	src->buffer = new->buffer;
	src->length = new->length;
	string_destroy(new, 0);
}

void				string_lcat(t_string *dst, t_u64 start,
						t_string *src, t_u64 length)
{
	if (dst->length < start || src->length < length
			|| dst->length - start < length)
		return ;
	ft_memcpy(dst->buffer + start, src->buffer, length);
}

void				string_destroy(t_string *string, int free_buffer)
{
	if (free_buffer)
		free(string->buffer);
	free(string);
}
