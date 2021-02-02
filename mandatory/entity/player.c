/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:53:03 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void			player_init(t_game *g)
{
	t_entity	*p;
	double		theta;

	p = &g->player;
	p->type = Entity_Player;
	p->size = entity_get_size(p->type);
	p->look_speed = PLAYER_LOOK_SPEED;
	p->move_speed = PLAYER_MOVE_SPEED;
	p->dir = vec_new(1.0, 0.0);
	p->plane = vec_new(0.0, tan(FIELD_OF_VIEW * M_PI / 360.0));
	if (g->map.startdir == 'N')
		theta = -M_PI_2;
	else if (g->map.startdir == 'S')
		theta = M_PI_2;
	else if (g->map.startdir == 'W')
		theta = M_PI;
	else
		theta = 0.0;
	p->dir = vec_rot(p->dir, theta);
	p->plane = vec_rot(p->plane, theta);
	p->pos = point_to_vector(g->map.startpos);
	p->pos = vec_add(p->pos, p->size);
}

static void		update_geometry(t_game *g, t_entity *p)
{
	t_map		*m;

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
		entity_rotate(p, Direction_Left);
	else if (g->input.key[Key_RightArrow])
		entity_rotate(p, Direction_Right);
}

void			player_update(t_game *g)
{
	t_entity	*p;

	p = &g->player;
	update_geometry(g, p);
}
