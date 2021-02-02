/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 17:13:48 by smun              #+#    #+#             */
/*   Updated: 2020/10/05 01:28:02 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(const char *s, const char *set)
{
	char		*str;
	size_t		len;
	size_t		begin;
	size_t		end;

	len = ft_strlens(s);
	begin = 0;
	end = 0;
	if (len > 0)
	{
		end = len - 1;
		while (begin < len && ft_strchr(set, s[begin]))
			begin++;
		while (begin <= end && ft_strchr(set, s[end]))
			end--;
		len = end - begin + 1;
	}
	if ((str = (char*)malloc(len + 1)))
		ft_strlcpy(str, &s[begin], len + 1);
	return (str);
}
