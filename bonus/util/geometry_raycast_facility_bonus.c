/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_raycast_facility_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:33:28 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 03:11:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

/*
** 1. Is the hit axis the same as the one that hit on the door block?
**  - If not, hit into the door wall before it passes.
**
** 2. Is the decimal part of the coordinate corresponding to the collision axis
** between 0.5 spaces greater than the opening of the door?
**  - If small, ray hits the door.
*/

t_bool			geometry_raycast_door(t_game *g, t_raycast *r, t_vector2 *ray)
{
	t_door		*door;
	int			axis;
	double		val;
	double		f;

	door = door_get(&g->map, r->mappos.x, r->mappos.y);
	if (!door)
		return (FALSE);
	axis = r->total.x < r->total.y ? Axis_X : Axis_Y;
	val = vec_get(&r->total, axis) + fabs(0.5 / vec_get(ray, axis));
	if (vec_get(&r->total, !axis) < val)
		return (FALSE);
	f = util_getf(vec_get(&r->origin, !axis) + val * vec_get(ray, !axis));
	if (f < door->factor)
	{
		r->factor = door->factor;
		return (vec_set(&r->total, axis, val));
	}
	return (FALSE);
}

t_bool			geometry_raycast_secret(t_game *g, t_raycast *r, t_vector2 *ry)
{
	t_secret	*secret;
	int			axis;
	double		val;

	secret = secret_get(&g->map, r->mappos.x, r->mappos.y);
	if (!secret || secret->state == SecretState_Revealed)
		return (FALSE);
	if (secret->state == SecretState_Unrevealed)
		return (TRUE);
	axis = r->total.x < r->total.y ? Axis_X : Axis_Y;
	val = vec_get(&r->total, axis) + fabs(secret->factor / vec_get(ry, axis));
	if (!(vec_get(&r->total, !axis) < val))
		return (vec_set(&r->total, axis, val));
	return (FALSE);
}
