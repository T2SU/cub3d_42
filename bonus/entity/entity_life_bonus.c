/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_life_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 18:08:56 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 06:26:54 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

void			entity_life_init(t_game *g, t_entity *e, t_point pt)
{
	int			block;

	entity_life_init_appearance(e->type, &e->life);
	e->life.frametick = 4;
	block = map_get(&g->map, pt.x, pt.y);
	if (block == 'n' || block == 's')
		e->dir.y = (block == 'n' ? -1 : 1);
	if (block == 'w' || block == 'e')
		e->dir.x = (block == 'w' ? -1 : 1);
	if (block == 'X')
		e->dir = vec_new(0.0, -1.0);
	e->plane = vec_new(0.0, tan(FIELD_OF_VIEW * M_PI / 360.0));
	e->plane = vec_rotraw(&e->plane, &e->dir);
	e->move_speed = ENEMY_MOVE_SPEED;
	e->look_speed = ENEMY_LOOK_SPEED;
	entity_life_init_soldier(g, e->type, e);
}

static void		update_life_frame(t_game *g, t_entity *e, t_bool loop)
{
	t_texset	*tex;
	int			imgcnt;
	t_life		*life;

	life = &e->life;
	if (life->frametick && g->tick.loopcnt % life->frametick)
		return ;
	tex = g->resource.texs[life->texid[life->state]];
	imgcnt = tex->imgcnt;
	if (entity_life_is_oriented_state(life->state))
		imgcnt /= life->orientnum;
	if (loop || life->i + 1 < imgcnt)
		life->i = (life->i + 1) % imgcnt;
	if (life->statedur && --life->statedur == 0)
		entity_life_set_state(g, e, LifeState_Walk, 0);
}

static void		play_sound(t_game *g, t_entity *e, t_life *life, int s)
{
	int			r;

	r = util_random_int();
	if (life->state == LifeState_Stand && s == LifeState_Walk)
	{
		sound_play(g, Sound_EnemyHello1 + (r & 1), e->pos, FALSE);
		if (e->type == Entity_Enemy2)
		{
			sound_stop(g, Sound_BGM1);
			sound_play(g, Sound_BGM2, e->pos, TRUE);
		}
	}
	else if (s == LifeState_Hit)
		sound_play(g, Sound_EnemyHit, e->pos, FALSE);
	else if (s == LifeState_Die)
		sound_play(g, Sound_EnemyDie1 + (r & 1), e->pos, FALSE);
	else if (s == LifeState_Attack)
		sound_play(g, life->weapon->gunsound, e->pos, FALSE);
}

void			entity_life_set_state(t_game *g, t_entity *e, int s, size_t t)
{
	t_life		*life;

	life = &e->life;
	play_sound(g, e, life, s);
	life->state = s;
	life->statedur = t;
	life->i = 0;
	life->delaydur = 8;
}

void			entity_life_update(t_game *g, t_entity *e)
{
	t_life		*life;

	if (!entity_is_life(e->type))
		return ;
	life = &e->life;
	if (e->hp > 0)
	{
		entity_life_ai_update(g, e);
		weapon_update(g, e, NULL);
		update_life_frame(g, e, TRUE);
	}
	else
	{
		if (life->state != LifeState_Die)
			entity_life_set_state(g, e, LifeState_Die, 0);
		update_life_frame(g, e, FALSE);
	}
}
