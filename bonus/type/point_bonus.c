/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:00:42 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

t_point			point_from_vector(t_vector2 vec)
{
	return (point_new((int)vec.x, (int)vec.y));
}

t_point			point_new(int x, int y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	return (p);
}

t_vector2		point_to_vector(t_point pt)
{
	return (vec_new(pt.x, pt.y));
}

t_point			point_next_by_dir(t_vector2 pos, t_vector2 dir)
{
	t_point	pt;

	pt = point_from_vector(pos);
	if (fabs(dir.x) > fabs(dir.y))
		pt.x += util_sign(dir.x);
	else
		pt.y += util_sign(dir.y);
	return (pt);
}
