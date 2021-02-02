/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:21:15 by smun              #+#    #+#             */
/*   Updated: 2020/10/04 16:09:44 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_overlapping(unsigned char *target,
					const unsigned char *origin,
					size_t len)
{
	return (origin < target && target < origin + len);
}

static void		copy_as_forward(unsigned char *target,
					const unsigned char *origin,
					size_t len)
{
	while (len-- > 0)
		if (target || origin)
			*(target++) = *(origin++);
}

static void		copy_as_backward(unsigned char *target,
					const unsigned char *origin,
					size_t len)
{
	while (len-- > 0)
		if (target || origin)
			target[len] = origin[len];
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*origin = (const unsigned char*)src;
	unsigned char		*target;

	target = (unsigned char*)dst;
	if (is_overlapping(target, origin, len))
		copy_as_backward(target, origin, len);
	else
		copy_as_forward(target, origin, len);
	return (dst);
}
