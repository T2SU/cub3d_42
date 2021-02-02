/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_raycast_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:18:53 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:50:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static int		get_orient(t_raycast *r, double rx, double ry)
{
	if (r->hit_axis == Axis_X)
	{
		if (rx < 0)
			return ('W');
		else
			return ('E');
	}
	else
	{
		if (ry < 0)
			return ('N');
		else
			return ('S');
	}
}

static t_bool	is_blocked(t_game *g, t_raycast *r, t_vector2 *ray, int md)
{
	if (map_is(&g->map, r->mappos.x, r->mappos.y, &block_is_wall))
		return (TRUE);
	if (map_is(&g->map, r->mappos.x, r->mappos.y, &block_is_door))
		return (geometry_raycast_door(g, r, ray));
	if (map_is(&g->map, r->mappos.x, r->mappos.y, &block_get_secret_look))
		return (geometry_raycast_secret(g, r, ray));
	if ((md & Raycast_Life))
		if (geometry_raycast_life(g, r, ray))
			return (TRUE);
	if ((md & Raycast_Player))
		if (geometry_raycast_user(g, r, ray))
			return (TRUE);
	return (FALSE);
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
**
** total.x  < total.y ==> Axis_X
** total.x >= total.y ==> Axis_Y
**   Axis_X   ===>   total.x
**   Axis_Y   ===>   total.y
*/

static void		init_raycast(t_raycast *r, t_vector2 *o, t_vector2 *ry)
{
	r->origin = *o;
	r->mappos.x = (int)o->x;
	r->mappos.y = (int)o->y;
	r->total.x = (r->mappos.x - o->x + (ry->x < 0 ? 0 : 1)) / ry->x;
	r->total.y = (r->mappos.y - o->y + (ry->y < 0 ? 0 : 1)) / ry->y;
	r->factor = -1;
	r->hitlife = NULL;
}

t_raycast		geometry_raycast(t_game *g, t_vector2 o, t_vector2 ry, int md)
{
	t_raycast	r;

	init_raycast(&r, &o, &ry);
	while (TRUE)
	{
		if (r.total.x < r.total.y)
			r.mappos.x += util_sign(ry.x);
		else
			r.mappos.y += util_sign(ry.y);
		if (is_blocked(g, &r, &ry, md))
		{
			r.hit_axis = r.total.x < r.total.y;
			r.collided.x = o.x + fmin(r.total.x, r.total.y) * ry.x;
			r.collided.y = o.y + fmin(r.total.x, r.total.y) * ry.y;
			r.orient = get_orient(&r, ry.x, ry.y);
			return (r);
		}
		if (r.total.x < r.total.y)
			r.total.x += fabs(1 / ry.x);
		else
			r.total.y += fabs(1 / ry.y);
	}
}
