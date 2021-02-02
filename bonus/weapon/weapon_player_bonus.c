/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 00:39:25 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 18:02:00 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_bool	process_ammo(t_game *g, t_weapon *wp)
{
	int			i;
	int			bullet;

	if (wp->ammo && g->bullets[wp->ammo] <= 0)
	{
		i = Weapon_Num;
		while (--i >= 0)
		{
			bullet = g->bullets[g->weapons[i].ammo];
			if ((g->inventory & (1 << i)) && (bullet > 0 || i == Weapon_Foot))
				break ;
		}
		weapon_player_switch(g, &g->player, i);
		return (FALSE);
	}
	if (!(g->cheat & Cheat_Ammo))
		g->bullets[wp->ammo]--;
	return (TRUE);
}

void			weapon_player_fire(t_game *g, t_entity *p)
{
	t_weapon	*wp;
	t_raycast	r;
	int			damage;

	wp = p->life.weapon;
	if (p->life.delaydur || !process_ammo(g, wp))
		return ;
	r = geometry_raycast(g, p->pos, p->dir, Raycast_Life);
	texset_resetframe(g, hud_to_resid(g, Hud_Weapon));
	p->life.attackdur = wp->speed;
	p->life.delaydur = wp->delay;
	entity_life_ai_feel_bullet(g, p);
	sound_play(g, wp->gunsound, p->pos, FALSE);
	if (r.hitlife == NULL)
		return ;
	damage = weapon_calc_damage(wp, p, r.hitlife->pos);
	if (damage && (g->cheat & Cheat_OneShot))
		damage = 99999999;
	r.hitlife->hp = ft_max(0, r.hitlife->hp - damage);
	if (r.hitlife->hp > 0 && damage > 0)
		entity_life_set_state(g, r.hitlife, LifeState_Hit, 2);
	g->attention = r.hitlife;
}

void			weapon_player_switch(t_game *g, t_entity *p, int forced)
{
	int			target;

	target = forced;
	if (g->input.key[Key_1])
		target = Weapon_Foot;
	else if (g->input.key[Key_2])
		target = Weapon_Pistol;
	else if (g->input.key[Key_3])
		target = Weapon_Shotgun;
	if (target < Weapon_Foot || target >= Weapon_Num)
		return ;
	if ((p->life.delaydur && forced < 0) || !(g->inventory & (1 << target)))
		return ;
	p->life.weapon = &g->weapons[target];
	texset_resetframe(g, hud_to_resid(g, Hud_Weapon));
	p->life.delaydur = 5;
}
