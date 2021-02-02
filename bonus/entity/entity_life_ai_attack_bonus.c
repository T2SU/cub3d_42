/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_life_ai_attack_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:26:29 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:40:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_bool		can_be_in_sight(t_game *g, t_entity *e)
{
	t_raycast		r;
	t_vector2		raydir;

	if ((g->cheat & Cheat_Transcendence))
		return (FALSE);
	raydir = vec_norm(vec_sub(g->player.pos, e->pos));
	r = geometry_raycast(g, e->pos, raydir, Raycast_Player);
	if (r.hitlife != NULL && r.hitlife->hp > 0)
	{
		e->dir = raydir;
		return (TRUE);
	}
	return (FALSE);
}

void				entity_life_ai_attack(t_game *g, t_entity *e)
{
	int				damage;
	t_weapon		*wp;

	if (e->life.delaydur)
		return ;
	if (!can_be_in_sight(g, e))
	{
		entity_life_set_state(g, e, LifeState_Walk, 0);
		return ;
	}
	wp = e->life.weapon;
	if (e->life.continousatk)
		entity_life_set_state(g, e, LifeState_Attack, 0);
	else
		entity_life_set_state(g, e, LifeState_Attack, 3);
	damage = weapon_calc_damage(wp, e, g->player.pos);
	player_hit(g, damage);
	if (e->life.continousatk)
		e->life.delaydur = wp->delay;
	else
		e->life.delaydur = wp->delay * 8;
}
