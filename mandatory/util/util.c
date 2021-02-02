/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:41:05 by smun              #+#    #+#             */
/*   Updated: 2021/01/18 21:50:27 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

t_bool		util_is_digits(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (ft_strlen(&str[i]) == 0)
		return (FALSE);
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (str[i] < '0' || str[i] > '9')
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

t_bool		util_is_empty_line(t_cchar *s)
{
	if (ft_strlen(s) == 0)
		return (TRUE);
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
			return (FALSE);
		s++;
	}
	return (TRUE);
}

void		util_unify_spaces(char **ps)
{
	char	*s;

	if (ps && (s = *ps))
	{
		while (*s)
		{
			if (*s == '\t' || *s == '\r')
				*s = ' ';
			s++;
		}
	}
}

int			util_sign(double nb)
{
	return (nb < 0 ? -1 : 1);
}

int			util_chrcnt(const char *s, int c)
{
	int		i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}
