/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_life_ai_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:29:18 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:41:00 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
**  Make active when player is in life's sight
**    or, feel bullet mark in its sight.
**
**  - player can be found by raycasting of entity's sight.
**  - A bullet mark can be detected by using a weapon
**    when life is in the player's sight.
*/

static t_bool	is_player_in_sight(t_game *g, t_entity *e)
{
	int			i;
	t_vector2	raydir;
	t_raycast	rc;
	double		x;

	i = 0;
	while (i < 15)
	{
		x = 2 * (i / 15.0) - 1;
		raydir.x = e->dir.x + e->plane.x * x;
		raydir.y = e->dir.y + e->plane.y * x;
		rc = geometry_raycast(g, e->pos, raydir, Raycast_Player);
		if (rc.hitlife != NULL)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
**  Cross Product
**  (because of it is 2D, z value is 0)
**
**  [ i j k ]
**  [ a b 0 ] = (ad - bc)k
**  [ c d 0 ]
**
** ad - bc = e->dir.x * dist.y - e->dir.y * dist.x
**
** note: https://bowbowbow.tistory.com/14
*/

static void		rotate_life(t_game *g, t_entity *e)
{
	t_entity	*p;
	t_vector2	dist;
	double		k;

	p = &g->player;
	dist = vec_norm(vec_sub(p->pos, e->pos));
	k = e->dir.x * dist.y - e->dir.y * dist.x;
	if (k > 0)
		entity_rotate(e, Direction_Right, 0.0);
	else
		entity_rotate(e, Direction_Left, 0.0);
}

static void		move_life(t_game *g, t_entity *e)
{
	t_vector2	ppt;

	if (g->tick.loopcnt % e->life.frametick)
		return ;
	ppt.x = e->pos.x + util_sign(e->dir.x) * (e->move_speed + e->size.x / 2);
	ppt.y = e->pos.y + util_sign(e->dir.y) * (e->move_speed + e->size.y / 2);
	if (!map_is_walkable(&g->map, (int)ppt.x, (int)ppt.y) ||
		(util_random_int() & 7) == 0)
		rotate_life(g, e);
	entity_move(&g->map, e, Direction_Forward);
}

void			entity_life_ai_update(t_game *g, t_entity *e)
{
	if (e->life.state == LifeState_Stand)
		if (is_player_in_sight(g, e))
			entity_life_set_state(g, e, LifeState_Walk, 0);
	if (e->life.state == LifeState_Walk)
	{
		move_life(g, e);
		entity_life_ai_attack(g, e);
	}
	else if (e->life.continousatk && e->life.state == LifeState_Attack)
		entity_life_ai_attack(g, e);
}

void			entity_life_ai_feel_bullet(t_game *g, t_entity *p)
{
	int			i;
	t_vector2	raydir;
	t_raycast	rc;
	double		x;

	i = 0;
	while (i < 15)
	{
		x = 2 * (i / 15.0) - 1;
		raydir.x = p->dir.x + p->plane.x * x;
		raydir.y = p->dir.y + p->plane.y * x;
		rc = geometry_raycast(g, p->pos, raydir, Raycast_Life);
		if (rc.hitlife != NULL && rc.hitlife->life.state == LifeState_Stand)
			entity_life_set_state(g, rc.hitlife, LifeState_Walk, 0);
		i++;
	}
}
