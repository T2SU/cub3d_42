/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 23:11:56 by smun              #+#    #+#             */
/*   Updated: 2021/01/20 15:36:18 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		len;
	size_t		slen;
	size_t		cpysize;

	len = 0;
	slen = ft_strlen(src);
	while (dst[len] != '\0' && dstsize > 0)
	{
		len++;
		dstsize--;
	}
	if (dstsize > 0)
	{
		cpysize = ft_min(slen, dstsize - 1);
		ft_memcpy(&dst[len], src, cpysize);
		dst[len + cpysize] = '\0';
	}
	return (slen + len);
}
