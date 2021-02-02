/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:36:22 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 17:49:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int		get_orient(t_raycast *r, t_vector2 ray)
{
	if (r->hit_axis == Axis_X)
	{
		if (ray.x < 0)
			return ('W');
		else
			return ('E');
	}
	else
	{
		if (ray.y < 0)
			return ('N');
		else
			return ('S');
	}
}

/*
**  Raycasting
**    ref: https://lodev.org/cgtutor/raycasting.html
**         https://blog.naver.com/aoikazto/221433793310
**         https://en.wikipedia.org/wiki/Ray_casting
**         https://www.youtube.com/watch?v=gYRrGTC7GtA
**         https://www.youtube.com/watch?v=eOCQfxRQ2pY
**         https://github.com/365kim/raycasting_tutorial
**         https://www.notion.so/20210111-b9fcbc89df0b4224b2cd834d4f92c6e6
**  Preforms raycasting with DDA.
**
** dir.x = ray.x < 0 ? -1 : 1
** total.x = fabs(1 / ray.x) * (dir.x * (pos.x - org.x) + ft_max(0, dir.x));
**
**  1. ray.x >= 0
**   1 / ray.x * (1 * (pos.x - org.x) + 1)
**   = (pos.x - org.x + 1) / ray.x
**  2. ray.x < 0
**   -1 / ray.x * (-1 * (pos.x - org.x) + 0)
**   = (pos.x - org.x + 0) / ray.x
**
** ==> (pos.x - org.x + (ray.x < 0 ? 0 : 1)) / ray.x
*/

t_raycast		geometry_raycast(t_game *g, t_vector2 org, t_vector2 ray)
{
	t_raycast	r;
	t_vector2	total;

	r.mappos = point_from_vector(org);
	total.x = (r.mappos.x - org.x + (ray.x < 0 ? 0 : 1)) / ray.x;
	total.y = (r.mappos.y - org.y + (ray.y < 0 ? 0 : 1)) / ray.y;
	while (TRUE)
	{
		if ((r.hit_axis = total.x < total.y))
			r.mappos.x += util_sign(ray.x);
		else
			r.mappos.y += util_sign(ray.y);
		if (map_is_wall(&g->map, r.mappos.x, r.mappos.y))
		{
			r.collided.x = org.x + fmin(total.x, total.y) * ray.x;
			r.collided.y = org.y + fmin(total.x, total.y) * ray.y;
			r.orient = get_orient(&r, ray);
			return (r);
		}
		if (r.hit_axis == Axis_X)
			total.x += fabs(1 / ray.x);
		else
			total.y += fabs(1 / ray.y);
	}
}

double			geometry_correct(t_raycast *r, t_vector2 rd)
{
	double		xfrac;

	if (r->hit_axis == Axis_X)
	{
		xfrac = r->collided.y - floor(r->collided.y + (signbit(rd.x) != 0));
		xfrac *= util_sign(rd.x);
	}
	else
	{
		xfrac = r->collided.x - floor(r->collided.x + (signbit(-rd.y) != 0));
		xfrac *= -util_sign(rd.y);
	}
	return (xfrac);
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
