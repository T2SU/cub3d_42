/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:30:13 by smun              #+#    #+#             */
/*   Updated: 2020/10/05 18:39:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		make_big_one(size_t c)
{
	size_t			data;

	data = (c & 0xff);
	data |= (data << 8);
	data |= (data << 16);
	if (sizeof(size_t) >= 8)
		data |= (data << 32);
	return (data);
}

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dest;
	size_t			*dest_large;
	size_t			data;
	size_t			i;

	data = make_big_one(c);
	dest = (unsigned char*)b;
	i = len % sizeof(size_t);
	while (i--)
		*(dest++) = c;
	dest_large = (size_t*)dest;
	i = len / sizeof(size_t);
	while (i--)
		*(dest_large++) = data;
	return (b);
}
