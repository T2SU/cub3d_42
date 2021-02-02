/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:16:18 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

t_rect		rect_new(double l, double t, double w, double h)
{
	t_rect	r;

	r.left = l;
	r.top = t;
	r.width = w;
	r.height = h;
	return (r);
}

/*
**  Pivot is center middle.
*/

t_rect		rect_from_size(t_vector2 pos, t_vector2 sz)
{
	t_vector2	offset;

	offset = vec_mult_scalar(sz, 0.5);
	return (rect_new(pos.x - offset.x, pos.y - offset.y, sz.x, sz.y));
}

t_bool		rect_contains(t_rect rc, t_vector2 pos)
{
	return (rc.left <= pos.x && rc.top <= pos.y &&
			rc.left + rc.width >= pos.x && rc.top + rc.height >= pos.y);
}

/*
**  https://www.geeksforgeeks.org/find-two-rectangles-overlap/
**  https://stackoverflow.com/questions/306316
*/

t_bool		rect_overlaps(t_rect rc, t_rect rc2)
{
	t_rect	*d1;
	t_rect	*d2;

	d1 = rc.left > rc2.left ? &rc2 : &rc;
	d2 = rc.left > rc2.left ? &rc : &rc2;
	if (d1->left + d1->width < d2->left)
		return (FALSE);
	d1 = rc.top > rc2.top ? &rc2 : &rc;
	d2 = rc.top > rc2.top ? &rc : &rc2;
	if (d1->top + d1->height < d2->top)
		return (FALSE);
	return (TRUE);
}
