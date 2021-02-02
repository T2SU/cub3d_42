/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_qsort_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 16:59:11 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 20:46:49 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Do swap each parameters
*/

static void	swap(t_fpair **tab, int a, int b)
{
	t_fpair	c;

	c = (*tab)[a];
	(*tab)[a] = (*tab)[b];
	(*tab)[b] = c;
}

/*
** Perform a quick-sort.
** https://en.wikipedia.org/wiki/Quicksort
** https://www.geeksforgeeks.org/quick-sort/
*/

static void	qsort(t_fpair **tab, int begin, int end)
{
	int		c;
	int		i;

	if (begin >= end)
		return ;
	i = begin;
	c = begin;
	while (i <= end)
	{
		if ((*tab)[i].f <= (*tab)[end].f)
			swap(tab, c++, i);
		i++;
	}
	qsort(tab, begin, c - 2);
	qsort(tab, c, end);
}

/*
** Main sort function
*/

void		util_qsort(t_fpair **tab, int size)
{
	qsort(tab, 0, size - 1);
}
