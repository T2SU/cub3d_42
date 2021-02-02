/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:21:00 by smun              #+#    #+#             */
/*   Updated: 2020/10/04 15:50:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			*ft_strdup(const char *s1)
{
	size_t		len;
	char		*s;

	len = ft_strlen(s1);
	if ((s = (char*)malloc(len + 1)))
		ft_strlcpy(s, s1, len + 1);
	return (s);
}
