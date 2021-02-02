/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_const_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:52:12 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:44:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

double				hud_scale(t_game *g, int type)
{
	if (type == Hud_Score)
		return (0.05);
	else if (type == Hud_Digit)
		return (0.75);
	else if (type == Hud_Hp)
		return (0.05);
	else if (type == Hud_Ammo)
		return (0.03);
	else if (type == Hud_Weapon)
	{
		if (g->player.life.weapon == &g->weapons[Weapon_Shotgun])
			return (0.3);
		else
			return (0.225);
	}
	else if (type == Hud_Crosshair)
		return (0.025);
	else if (type == Hud_Lifebar)
		return (0.4);
	else if (type == Hud_LifeGauge)
		return (0.345);
	return (1.0);
}

t_point				hud_offset(t_game *g, int type)
{
	t_point			ret;
	t_size			sz;
	t_point			wh;

	wh.x = g->screensize.width;
	wh.y = g->screensize.height;
	sz = hud_size(g, type);
	ret = point_new(0, 0);
	if (type == Hud_Score)
		ret = point_new(30, wh.y - sz.height - 30);
	else if (type == Hud_Hp)
		ret = point_new(30, hud_offset(g, Hud_Score).y - sz.height - 20);
	else if (type == Hud_Ammo)
		ret = point_new(wh.x - sz.width - 100, wh.y - sz.height - 30);
	else if (type == Hud_Crosshair)
		ret = point_new(wh.x / 2 - sz.width / 2, wh.y / 2 - sz.height / 2);
	else if (type == Hud_Weapon && weapon_cur(g) == Weapon_Foot)
		ret = point_new(wh.x / 2 - sz.width / 2, wh.y - sz.height);
	else if (type == Hud_Weapon && weapon_cur(g) == Weapon_Shotgun)
		ret = point_new(wh.x / 2 + sz.width / 2, wh.y - sz.height);
	else if (type == Hud_Weapon)
		ret = point_new(wh.x / 2 + sz.width, wh.y - sz.height);
	else if (type == Hud_Lifebar)
		ret = point_new(wh.x / 2 - sz.width / 2, 20);
	return (point_new(ft_max(0, ret.x), ft_max(0, ret.y)));
}

t_size				hud_size(t_game *g, int type)
{
	t_size			ret;
	t_image			*img;
	double			scale;

	img = texset_get_img(g, hud_to_resid(g, type));
	if (!img)
		return (size_new(0, 0));
	scale = hud_scale(g, type);
	ret.width = (int)(scale * g->screensize.width);
	ret.height = ret.width * img->size.height / img->size.width;
	return (ret);
}

static int			get_resid_sub(t_game *g, int id)
{
	if (id == Hud_Ammo)
	{
		if (g->player.life.weapon == &g->weapons[Weapon_Pistol])
			return (Id_Weapon1A);
		else if (g->player.life.weapon == &g->weapons[Weapon_Shotgun])
			return (Id_Weapon2A);
	}
	else if (id == Hud_Weapon)
	{
		if (g->player.life.weapon == &g->weapons[Weapon_Pistol])
			return (Id_Weapon1);
		else if (g->player.life.weapon == &g->weapons[Weapon_Shotgun])
			return (Id_Weapon2);
		else if (g->player.life.weapon == &g->weapons[Weapon_Foot])
			return (Id_Weapon0);
	}
	return (Id_Null);
}

int					hud_to_resid(t_game *g, int id)
{
	if (id == Hud_Score)
		return (Id_HudScore);
	else if (id == Hud_Digit)
		return (Id_Digit);
	else if (id == Hud_Hp)
		return (Id_HudHp);
	else if (id == Hud_Ammo || id == Hud_Weapon)
		return (get_resid_sub(g, id));
	else if (id == Hud_Crosshair)
		return (Id_Crosshair);
	else if (id == Hud_Lifebar)
		return (Id_HudHPBar);
	else if (id == Hud_LifeGauge)
		return (Id_HudHPGauge);
	else if (id == Hud_GameOver)
	{
		if (g->gameover == GameOver_Dead)
			return (Id_GameOver);
		else
			return (Id_GameWin);
	}
	return (Id_Null);
}
