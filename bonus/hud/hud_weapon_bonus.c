/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_weapon_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:16:25 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 15:43:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		draw_weapon_ammo(t_game *g)
{
	t_size		size;
	t_point		offset;
	int			ammo;

	size = hud_size(g, Hud_Ammo);
	offset = hud_offset(g, Hud_Ammo);
	hud_put(g, offset, size, hud_to_resid(g, Hud_Ammo));
	ammo = g->bullets[g->player.life.weapon->ammo];
	hud_draw_digit(g, hud_middle_offset(g, offset, size, Hud_Digit), ammo);
}

void			hud_draw_weapon(t_game *g)
{
	t_size		size;
	t_point		offset;

	if (g->gameover != GameOver_None)
		return ;
	size = hud_size(g, Hud_Weapon);
	offset = hud_offset(g, Hud_Weapon);
	hud_put(g, offset, size, hud_to_resid(g, Hud_Weapon));
	if (g->player.life.weapon->ammo != Ammo_None)
		draw_weapon_ammo(g);
	size = hud_size(g, Hud_Crosshair);
	offset = hud_offset(g, Hud_Crosshair);
	hud_put(g, offset, size, hud_to_resid(g, Hud_Crosshair));
}
