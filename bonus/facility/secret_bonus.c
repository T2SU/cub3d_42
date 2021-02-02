/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:56:58 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 19:34:49 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_secret		*secret_get(t_map *m, int x, int y)
{
	int			i;
	t_secret	*s;

	i = map_get_attr(m, x, y);
	if (i && (s = m->secret[i - 1]))
		return (s);
	return (NULL);
}

t_bool			secret_interact(t_game *g, t_entity *p, t_point pos)
{
	t_secret	*s;

	if (!facility_can_interact(pos, p))
		return (FALSE);
	if (!(s = secret_get(&g->map, pos.x, pos.y)))
		return (FALSE);
	if (s->state == SecretState_Unrevealed)
	{
		s->nextpos = point_next_by_dir(point_to_vector(s->pos), p->dir);
		s->state = SecretState_Moving;
	}
	return (TRUE);
}

static t_bool	activate_chain(t_game *g, t_point pt, t_point before)
{
	t_point		dir;
	t_secret	*s;

	if (!map_is(&g->map, pt.x, pt.y, &block_get_secret_look))
		return (FALSE);
	if (!(s = secret_get(&g->map, pt.x, pt.y)))
		return (FALSE);
	if (s->state != SecretState_Unrevealed)
		return (FALSE);
	dir.x = pt.x - before.x;
	dir.y = pt.y - before.y;
	s->nextpos = point_new(pt.x + dir.x, pt.y + dir.y);
	s->state = SecretState_Moving;
	return (TRUE);
}

void			secret_update(t_game *g, t_secret *s)
{
	if (s->state != SecretState_Moving)
		return ;
	s->factor += SECRETWALL_SPEED;
	if (s->factor >= 1)
	{
		s->factor = 1;
		s->state = SecretState_Revealed;
		if (!activate_chain(g, s->nextpos, s->pos))
			sound_play(g, Sound_SecretWallEnd, point_to_vector(s->pos), FALSE);
	}
	else if (g->tick.loopcnt % s->soundtick == 0)
		sound_play(g, Sound_SecretWall, point_to_vector(s->pos), FALSE);
}

t_bool			secret_is_throughable(t_map *m, int x, int y)
{
	t_secret	*s;

	if (!(s = secret_get(m, x, y)))
		return (TRUE);
	return (s->state == SecretState_Revealed);
}
