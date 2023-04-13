/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_atoi_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 06:29:32 by smun              #+#    #+#             */
/*   Updated: 2023/04/13 14:53:02 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

static t_bool	check_overflow(long nbr, long num)
{
	return (nbr > 0 && (nbr * 10 + num) < 0);
}

static t_bool	check_underflow(long nbr, long num)
{
	return (nbr < 0 && (nbr * 10 + num) > 0);
}

static long		get_nbr(const char *str, long neg)
{
	long		nbr;
	long		num;

	nbr = 0;
	while (ft_isspace(*str) || (*str >= '0' && *str <= '9'))
	{
		if (!ft_isspace(*str))
		{
			num = neg * (*str - '0');
			if (check_overflow(nbr, num))
				return (-1);
			if (check_underflow(nbr, num))
				return (0);
			nbr = nbr * 10 + num;
		}
		str++;
	}
	return (nbr);
}

int				util_atoi(const char *str)
{
	long		neg;

	neg = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			neg = -neg;
	return ((int)get_nbr(str, neg));
}
