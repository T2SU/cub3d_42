/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:55:26 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector2		vec_new(double x, double y)
{
	t_vector2	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_bool			vec_set(t_vector2 *v, int axis, double val)
{
	if (axis == Axis_X)
		v->x = val;
	else
		v->y = val;
	return (TRUE);
}

double			vec_get(t_vector2 *v, int axis)
{
	if (axis == Axis_X)
		return (v->x);
	else
		return (v->y);
}
