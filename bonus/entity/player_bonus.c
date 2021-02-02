/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:53:03 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:41:39 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>
#include <libft.h>

void			player_init(t_game *g)
{
	t_entity	*p;

	p = &g->player;
	ft_bzero(p, sizeof(t_entity));
	p->type = Entity_Player;
	p->size = entity_get_size(p->type);
	p->look_speed = PLAYER_LOOK_SPEED;
	p->move_speed = PLAYER_MOVE_SPEED;
	if (g->map.startdir == 'N' || g->map.startdir == 'S')
		p->dir.y = (g->map.startdir == 'N' ? -1 : 1);
	if (g->map.startdir == 'W' || g->map.startdir == 'E')
		p->dir.x = (g->map.startdir == 'W' ? -1 : 1);
	p->plane = vec_new(0.0, tan(FIELD_OF_VIEW * M_PI / 360.0));
	p->plane = vec_rotraw(&p->plane, &p->dir);
	p->pos = vec_add(point_to_vector(g->map.startpos), p->size);
	p->hp = 120;
	p->maxhp = 120;
	p->life.weapon = &g->weapons[Weapon_Pistol];
	p->life.damagefactor = 1.0;
	g->bullets[Ammo_Bullet] = 20;
	g->inventory = (1 << Weapon_Foot) | (1 << Weapon_Pistol);
}

static void		update_geometry(t_game *g, t_entity *p)
{
	t_map		*m;
	double		x;

	m = &g->map;
	if (g->input.key[Key_W])
		entity_move(m, p, Direction_Forward);
	if (g->input.key[Key_S])
		entity_move(m, p, Direction_Backward);
	if (g->input.key[Key_A])
		entity_move(m, p, Direction_Left);
	if (g->input.key[Key_D])
		entity_move(m, p, Direction_Right);
	if (g->input.key[Key_LeftArrow])
		entity_rotate(p, Direction_Left, 0.0);
	else if (g->input.key[Key_RightArrow])
		entity_rotate(p, Direction_Right, 0.0);
	x = g->input.mousemoved.x * M_PI_4 / g->screensize.width;
	if (x < 0)
		entity_rotate(p, Direction_Left, x);
	else if (x > 0)
		entity_rotate(p, Direction_Right, x);
	g->input.mousemoved = vec_new(0, 0);
}

static void		update_interaction(t_game *g, t_entity *p)
{
	t_point		pt;

	if (!g->input.key[Key_Space])
		return ;
	pt = point_next_by_dir(p->pos, p->dir);
	if (map_is(&g->map, pt.x, pt.y, &block_is_door))
		door_interact(g, p, pt);
	else if (map_is(&g->map, pt.x, pt.y, &block_get_secret_look))
		secret_interact(g, p, pt);
	else if (map_is(&g->map, pt.x, pt.y, &block_is_exit))
		exit_interact(g, p);
	else
		sound_play(g, Sound_NoWay, p->pos, FALSE);
}

void			player_update(t_game *g)
{
	t_entity	*p;

	p = &g->player;
	if (g->gameovertick >= g->tick.loopcnt)
		return ;
	if (g->gameover != GameOver_None)
	{
		if (g->input.key[Key_Space])
			player_game_restart(g);
		return ;
	}
	update_geometry(g, p);
	update_interaction(g, p);
	player_try_pickup_item(g, p);
	if (g->input.key[Key_LCtrl] || g->input.mousebtn[MouseBtn_Left])
		weapon_player_fire(g, p);
	weapon_player_switch(g, p, -1);
	weapon_update(g, p, g->resource.texs[hud_to_resid(g, Hud_Weapon)]);
}

void			player_hit(t_game *g, int damage)
{
	t_entity	*p;

	if (damage <= 0)
		return ;
	p = &g->player;
	if (!(g->cheat & Cheat_God))
		p->hp = ft_max(0, p->hp - damage);
	if (p->hp == 0)
	{
		sound_play(g, Sound_PlayerDie, p->pos, FALSE);
		player_game_over(g);
	}
	else
	{
		sound_play(g, Sound_PlayerHit, p->pos, FALSE);
		screen_setcolormap(g, Color_LightRed, 5);
	}
}
