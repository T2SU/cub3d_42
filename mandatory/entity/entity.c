/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:32:58 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void			entity_init(t_game *g, t_entity *e, t_point pt, int c)
{
	t_vector2	scale;

	scale = entity_get_scale(c);
	e->scale.x = 1 / scale.x;
	e->scale.y = 1 / scale.y;
	e->type = c;
	e->pos = vec_new(pt.x + 0.5, pt.y + 0.5);
	e->size = entity_get_size(c);
	e->yoffset = entity_get_yoffset(c) * g->screensize.height;
}

void			entity_rotate(t_entity *e, int dir)
{
	double		theta;

	if (dir == Direction_Left)
		theta = -e->look_speed;
	else if (dir == Direction_Right)
		theta = e->look_speed;
	else
		theta = 0.0;
	e->dir = vec_rot(e->dir, theta);
	e->plane = vec_rot(e->plane, theta);
}

void			entity_move(t_map *m, t_entity *e, int dir)
{
	t_vector2	movevector;

	if (dir == Direction_Forward)
		movevector = e->dir;
	else if (dir == Direction_Backward)
		movevector = vec_rot(e->dir, M_PI);
	else if (dir == Direction_Left)
		movevector = vec_rot(e->dir, -M_PI_2);
	else if (dir == Direction_Right)
		movevector = vec_rot(e->dir, M_PI_2);
	else
		movevector = vec_new(0, 0);
	movevector = vec_mult_scalar(movevector, e->move_speed);
	movevector = map_alter_movevec(m, e, movevector);
	e->pos = vec_add(e->pos, movevector);
}
