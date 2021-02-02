/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 22:51:57 by smun              #+#    #+#             */
/*   Updated: 2020/10/04 15:50:44 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		truncate_len(size_t slen, size_t dstsize)
{
	return ((slen >= dstsize) ? (dstsize - 1) : (slen));
}

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			slen;
	size_t			cpylen;

	slen = ft_strlens(src);
	if (dstsize > 0)
	{
		cpylen = truncate_len(slen, dstsize);
		ft_memcpy(dst, src, cpylen);
		if (dst)
			dst[cpylen] = '\0';
	}
	return (slen);
}
