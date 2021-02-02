/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_life_const_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 00:27:28 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 05:31:45 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool			entity_is_life(int type)
{
	if (type == Entity_Enemy1)
		return (TRUE);
	else if (type == Entity_Enemy2)
		return (TRUE);
	return (FALSE);
}

t_bool			entity_life_is_oriented_state(int state)
{
	if (state == LifeState_Stand)
		return (TRUE);
	else if (state == LifeState_Walk)
		return (TRUE);
	else if (state == LifeState_Attack)
		return (TRUE);
	else if (state == LifeState_Hit)
		return (TRUE);
	return (FALSE);
}

void			entity_life_init_appearance(int type, t_life *life)
{
	if (type == Entity_Enemy1)
	{
		life->texid[LifeState_Stand] = Id_Enemy1Std;
		life->texid[LifeState_Walk] = Id_Enemy1Mov;
		life->texid[LifeState_Attack] = Id_Enemy1Atk;
		life->texid[LifeState_Hit] = Id_Enemy1Hit;
		life->texid[LifeState_Die] = Id_Enemy1Die;
		life->continousatk = FALSE;
	}
	if (type == Entity_Enemy2)
	{
		life->texid[LifeState_Stand] = Id_Enemy2Std;
		life->texid[LifeState_Walk] = Id_Enemy2Mov;
		life->texid[LifeState_Attack] = Id_Enemy2Atk;
		life->texid[LifeState_Hit] = Id_Enemy2Hit;
		life->texid[LifeState_Die] = Id_Enemy2Die;
		life->continousatk = TRUE;
	}
}

void			entity_life_init_soldier(t_game *g, int type, t_entity *e)
{
	if (type == Entity_Enemy1)
	{
		e->life.weapon = &g->weapons[Weapon_Pistol];
		e->life.damagefactor = 0.2;
		e->hp = 100;
		e->maxhp = 100;
		e->life.orientnum = 5;
	}
	if (type == Entity_Enemy2)
	{
		e->life.weapon = &g->weapons[Weapon_Chaingun];
		e->life.damagefactor = 0.1;
		e->hp = 2000;
		e->maxhp = 2000;
		e->life.orientnum = 8;
	}
}
