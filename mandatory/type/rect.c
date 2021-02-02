/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:16:18 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rect		rect_new(double l, double t, double w, double h)
{
	t_rect	r;

	r.left = l;
	r.top = t;
	r.width = w;
	r.height = h;
	return (r);
}

t_rect		rect_from_size(t_vector2 pos, t_vector2 sz)
{
	t_vector2	offset;

	offset = vec_mult_scalar(sz, 0.5);
	return (rect_new(pos.x - offset.x, pos.y - offset.y, sz.x, sz.y));
}
