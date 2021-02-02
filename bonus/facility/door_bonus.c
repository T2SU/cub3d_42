/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:56:45 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 19:04:30 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_door		*door_get(t_map *m, int x, int y)
{
	int		i;
	t_door	*d;

	i = map_get_attr(m, x, y);
	if (i && (d = m->door[i - 1]))
		return (d);
	return (NULL);
}

static void	set_door_state(t_game *g, t_door *door, int state)
{
	door->state = state;
	if (state == DoorState_Opening)
		sound_play(g, Sound_DoorOpen, point_to_vector(door->pos), FALSE);
	if (state == DoorState_Closing)
		sound_play(g, Sound_DoorClose, point_to_vector(door->pos), FALSE);
}

t_bool		door_interact(t_game *g, t_entity *p, t_point pos)
{
	t_door	*door;

	if (!facility_can_interact(pos, p))
		return (FALSE);
	if (!(door = door_get(&g->map, pos.x, pos.y)))
		return (FALSE);
	if (door->ignore_interact > g->tick.loopcnt)
		return (FALSE);
	if (door->state == DoorState_Open || door->state == DoorState_Opening)
		set_door_state(g, door, DoorState_Closing);
	else
		set_door_state(g, door, DoorState_Opening);
	door->ignore_interact = g->tick.loopcnt + 5;
	return (TRUE);
}

void		door_update(t_game *g, t_door *door)
{
	if (door->state == DoorState_Opening)
	{
		door->factor -= 0.03;
		if (door->factor <= 0)
		{
			door->factor = 0;
			set_door_state(g, door, DoorState_Open);
			door->closewait = g->tick.loopcnt + 50;
		}
	}
	else if (door->state == DoorState_Closing)
	{
		door->factor += 0.03;
		if (door->factor >= 1)
		{
			door->factor = 1;
			set_door_state(g, door, DoorState_Closed);
		}
	}
	else if (door->state == DoorState_Open)
	{
		if (g->tick.loopcnt >= door->closewait)
			if (!facility_is_in_someone(g, door->pos))
				set_door_state(g, door, DoorState_Closing);
	}
}

t_bool		door_is_throughable(t_map *m, int x, int y)
{
	t_door	*d;

	if (!(d = door_get(m, x, y)))
		return (TRUE);
	return (d->state == DoorState_Open);
}
