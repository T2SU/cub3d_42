/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_raycast_life_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:28:45 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:51:35 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static t_bool	is_hit(t_raycast *r, t_vector2 *ray, t_entity *e)
{
	t_vector2	frac;
	double		val;
	int			axis;
	double		delta;

	frac.x = e->pos.x - r->mappos.x;
	frac.y = e->pos.y - r->mappos.y;
	if (frac.x >= 0 && frac.x < 1 && frac.y >= 0 && frac.y < 1)
	{
		axis = r->total.x < r->total.y ? Axis_X : Axis_Y;
		delta = fabs(vec_get(&frac, axis) / vec_get(ray, axis));
		val = vec_get(&r->total, axis) + delta;
		if (vec_get(&r->total, !axis) < val)
			return (FALSE);
		val = vec_get(&r->origin, !axis) + val * vec_get(ray, !axis);
		if (vec_get(&e->pos, !axis) - (vec_get(&e->size, !axis) / 2) <= val &&
			vec_get(&e->pos, !axis) + (vec_get(&e->size, !axis) / 2) >= val)
		{
			vec_set(&r->total, axis, vec_get(&r->total, axis) + delta);
			return (TRUE);
		}
	}
	return (FALSE);
}

static t_bool	too_close_hit(t_game *g, t_entity *e)
{
	t_rect		rect;

	rect = rect_from_size(e->pos, e->size);
	if (rect_contains(rect, g->player.pos))
		return (TRUE);
	return (FALSE);
}

t_bool			geometry_raycast_life(t_game *g, t_raycast *r, t_vector2 *ray)
{
	t_list		*lst;
	t_entity	*e;

	lst = g->map.ent;
	while (lst)
	{
		e = (t_entity*)lst->content;
		if (entity_is_life(e->type) && e->hp > 0)
			if (too_close_hit(g, e) || is_hit(r, ray, e))
			{
				r->hitlife = e;
				return (TRUE);
			}
		lst = lst->next;
	}
	return (FALSE);
}

t_bool			geometry_raycast_user(t_game *g, t_raycast *r, t_vector2 *ry)
{
	if (is_hit(r, ry, &g->player))
	{
		r->hitlife = &g->player;
		return (TRUE);
	}
	return (FALSE);
}
