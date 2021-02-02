/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 21:52:44 by smun              #+#    #+#             */
/*   Updated: 2020/10/05 18:40:19 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*convrt(char *b, int n)
{
	if (n / 10)
		b = convrt(b, n / 10);
	*b = '0' + ft_abs(n % 10);
	return (b + 1);
}

char			*ft_itoa(int n)
{
	char		buf[32];
	char		*a;

	ft_bzero(buf, 32);
	if (n < 0)
		buf[0] = '-';
	convrt(&buf[n < 0], n);
	if ((a = malloc(1 + ft_strlen(buf))))
		ft_strlcpy(a, buf, 1 + ft_strlen(buf));
	return (a);
}
