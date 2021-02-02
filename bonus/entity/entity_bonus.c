/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:32:58 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 01:41:53 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

void				entity_init(t_game *g, t_entity *e, t_point pt, int c)
{
	t_vector2		scale;

	scale = entity_get_scale(c);
	e->scale.x = 1 / scale.x;
	e->scale.y = 1 / scale.y;
	e->type = c;
	e->pos = vec_new(pt.x + 0.5, pt.y + 0.5);
	e->size = entity_get_size(c);
	e->yoffset = entity_get_yoffset(c) * g->screensize.height;
	e->hp = 1;
	if (entity_is_life(e->type))
		entity_life_init(g, e, pt);
}

void				entity_rotate(t_entity *e, int dir, double theta)
{
	if (theta == 0.0)
	{
		if (dir == Direction_Left)
			theta = -e->look_speed;
		else if (dir == Direction_Right)
			theta = e->look_speed;
	}
	e->dir = vec_rot(e->dir, theta);
	e->plane = vec_rot(e->plane, theta);
}

void				entity_move(t_map *m, t_entity *e, int dir)
{
	t_vector2		movevector;

	if (dir == Direction_Forward)
		movevector = e->dir;
	else if (dir == Direction_Backward)
		movevector = vec_rot(e->dir, M_PI);
	else if (dir == Direction_Left)
		movevector = vec_rot(e->dir, -M_PI_2);
	else if (dir == Direction_Right)
		movevector = vec_rot(e->dir, M_PI_2);
	else
		movevector = vec_new(0, 0);
	movevector = vec_mult_scalar(movevector, e->move_speed);
	movevector = map_alter_movevec(m, e, movevector);
	e->pos = vec_add(e->pos, movevector);
}

/*
**  Atan2(Player's Direction) - Atan2(Entity's Direction)
**    --> Relative angle of entity to player.
*/

int					entity_get_view_orient(t_entity *e, t_entity *p)
{
	static double	cached[8];
	static double	pi2;
	double			angle;
	int				i;

	if (!cached[0])
	{
		i = 0;
		cached[0] = M_PI_4 / 2;
		while (++i < 8)
			cached[i] = cached[i - 1] + M_PI_4;
		pi2 = 2 * M_PI;
	}
	if (!entity_is_life(e->type))
		return (Orient_N);
	angle = atan2(p->dir.y, p->dir.x) - atan2(e->dir.y, e->dir.x);
	if (angle < 0)
		angle += pi2;
	i = Orient_N;
	while (++i < (Orient_Num))
		if (angle >= cached[i - 1] && angle < cached[i])
			return (i);
	return (Orient_N);
}

void				entity_update(t_game *g)
{
	t_list			*lst;
	t_entity		*e;

	lst = g->map.ent;
	while (lst)
	{
		e = (t_entity*)lst->content;
		if (entity_is_life(e->type))
			entity_life_update(g, e);
		lst = lst->next;
	}
}
