/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 02:16:36 by smun              #+#    #+#             */
/*   Updated: 2020/10/05 04:02:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;
	size_t			*dest_large;
	size_t			i;

	dest = (unsigned char*)s;
	i = n % sizeof(size_t);
	while (i--)
		*(dest++) = 0;
	dest_large = (size_t*)dest;
	i = n / sizeof(size_t);
	while (i--)
		*(dest_large++) = 0;
}
