/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:22:22 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 18:02:00 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static void	weapon_init2(t_game *g)
{
	g->weapons[Weapon_Chaingun].ammo = Ammo_Bullet;
	g->weapons[Weapon_Chaingun].damage = 10;
	g->weapons[Weapon_Chaingun].bullet = 1;
	g->weapons[Weapon_Chaingun].delay = 4;
	g->weapons[Weapon_Chaingun].speed = 3;
	g->weapons[Weapon_Chaingun].range = INFINITY;
	g->weapons[Weapon_Chaingun].spread = 0.03;
	g->weapons[Weapon_Chaingun].gunsound = Sound_Pistol;
}

void		weapon_init(t_game *g)
{
	g->weapons[Weapon_Foot].ammo = Ammo_None;
	g->weapons[Weapon_Foot].damage = 15;
	g->weapons[Weapon_Foot].bullet = 0;
	g->weapons[Weapon_Foot].delay = 7;
	g->weapons[Weapon_Foot].speed = 4;
	g->weapons[Weapon_Foot].range = 1.0;
	g->weapons[Weapon_Foot].spread = 0.0;
	g->weapons[Weapon_Foot].gunsound = Sound_Foot;
	g->weapons[Weapon_Pistol].ammo = Ammo_Bullet;
	g->weapons[Weapon_Pistol].damage = 35;
	g->weapons[Weapon_Pistol].bullet = 1;
	g->weapons[Weapon_Pistol].delay = 10;
	g->weapons[Weapon_Pistol].speed = 3;
	g->weapons[Weapon_Pistol].range = INFINITY;
	g->weapons[Weapon_Pistol].spread = 0.04;
	g->weapons[Weapon_Pistol].gunsound = Sound_Pistol;
	g->weapons[Weapon_Shotgun].ammo = Ammo_Shell;
	g->weapons[Weapon_Shotgun].damage = 35;
	g->weapons[Weapon_Shotgun].bullet = 4;
	g->weapons[Weapon_Shotgun].delay = 24;
	g->weapons[Weapon_Shotgun].speed = 2;
	g->weapons[Weapon_Shotgun].range = INFINITY;
	g->weapons[Weapon_Shotgun].spread = 0.09;
	g->weapons[Weapon_Shotgun].gunsound = Sound_Shotgun;
	weapon_init2(g);
}

void		weapon_update(t_game *g, t_entity *e, t_texset *tex)
{
	if (e->life.delaydur)
		e->life.delaydur--;
	if (e->life.attackdur && tex && (g->tick.loopcnt % e->life.attackdur) == 0)
	{
		if (tex->i + 1 == tex->imgcnt)
		{
			tex->i = 0;
			e->life.attackdur = 0;
		}
		else
			texset_nextframe(g, hud_to_resid(g, Hud_Weapon), FALSE);
	}
}

int			weapon_calc_damage(t_weapon *wp, t_entity *e, t_vector2 d)
{
	int		i;
	int		hit;
	double	dist;
	double	factor;

	dist = util_distance(e->pos, d);
	factor = e->life.damagefactor;
	if (wp->range < dist)
		return (0);
	if (wp->ammo == Ammo_None)
		return ((int)(wp->damage * factor));
	hit = 0;
	i = 0;
	while (i < wp->bullet)
	{
		if (util_random_double() < 1.0 - (dist * wp->spread))
			hit++;
		i++;
	}
	return ((int)(wp->damage * hit * factor));
}

int			weapon_cur(t_game *g)
{
	int		i;

	i = 0;
	while (i < Weapon_Num)
	{
		if (g->player.life.weapon == &g->weapons[i])
			return (i);
		i++;
	}
	return (Weapon_Foot);
}
