/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 18:42:55 by kyork             #+#    #+#             */
/*   Updated: 2018/02/21 21:36:18 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONTYPES_H
# define COMMONTYPES_H

# include <stdint.h>
# include <stddef.h>

typedef uint8_t			t_u8;
typedef uint16_t		t_u16;
typedef uint32_t		t_u32;
typedef uint64_t		t_u64;
typedef int8_t			t_s8;
typedef int16_t			t_s16;
typedef int32_t			t_s32;
typedef int64_t			t_s64;

/*
** Rudimentary length-tagged string library
** Mostly untested.
*/

typedef struct			s_string
{
	char	*buffer;
	t_u64	length;
}						t_string;

t_string				*string_create(t_u64 length);
t_string				*string_wrap(char *buffer, t_u64 length);
void					string_append(t_string *src, t_string *append);
void					string_lcat(t_string *dst, t_u64 start,
							t_string *src, t_u64 length);
void					string_destroy(t_string *string, int free_buffer);

#endif  // COMMONTYPES_H
