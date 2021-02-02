/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:36:22 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 17:49:54 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>
#include <libft.h>

/*
**  Make a texture's x fraction. (0 <= xfrac < 1)
**  base idea is (collided - floor(collided)).
**  if needs, do flip computation for correct texture rendering.
*/

double			geometry_correct(t_raycast *r, t_vector2 rd)
{
	double		frac;
	double		col;

	if (r->hit_axis == Axis_X)
	{
		col = r->collided.y;
		if (r->factor == -1)
			frac = (col - floor(col + (signbit(rd.x) != 0))) * util_sign(rd.x);
		else
			frac = 1 - (util_getf(col) - r->factor);
	}
	else
	{
		col = r->collided.x;
		if (r->factor == -1)
		{
			frac = (col - floor(col + (signbit(-rd.y) != 0)));
			frac *= -util_sign(rd.y);
		}
		else
			frac = 1 - (util_getf(col) - r->factor);
	}
	return (util_getf(frac));
}

/*
**  https://lodev.org/cgtutor/raycasting.html
**  Can be proved using triangles' same shape, different size.
*/

double			geometry_get_orthodist(t_game *g, t_raycast *r, t_vector2 rd)
{
	if (r->hit_axis == Axis_X)
		return ((r->collided.x - g->player.pos.x) / rd.x);
	else
		return ((r->collided.y - g->player.pos.y) / rd.y);
}

int				geometry_shade(double distance, int color)
{
	int			rpercent;
	t_uchar		*colors;

	if (distance < 1)
		return (color);
	rpercent = ft_min(700, ft_max(0, (int)(distance * 42)));
	colors = (t_uchar*)(&color);
	colors[0] = (t_uchar)(colors[0] * (1000 - rpercent) / 1000);
	colors[1] = (t_uchar)(colors[1] * (1000 - rpercent) / 1000);
	colors[2] = (t_uchar)(colors[2] * (1000 - rpercent) / 1000);
	return (color);
}
