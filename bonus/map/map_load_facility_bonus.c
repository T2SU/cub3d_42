/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_facility_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:54:38 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 02:48:51 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

static t_bool	is_walkable_block(t_map *m, int x, int y)
{
	return (map_is(m, x, y, &block_is_item) ||
			ft_strchr("SWNE0", map_get(m, x, y)));
}

static t_bool	n_d(t_game *g, t_point p, int d)
{
	t_map		*m;

	m = &g->map;
	if (!(m->door[d] = ft_calloc(1, sizeof(t_door))))
		return (error_raise(g, Error_System, "alloc door failed"));
	if (map_is(m, p.x - 1, p.y, &block_is_wall) &&
		map_is(m, p.x + 1, p.y, &block_is_wall) &&
		is_walkable_block(m, p.x, p.y - 1) &&
		is_walkable_block(m, p.x, p.y + 1))
		m->door[d]->axis = Axis_Y;
	else if (map_is(m, p.x, p.y - 1, &block_is_wall) &&
		map_is(m, p.x, p.y + 1, &block_is_wall) &&
		is_walkable_block(m, p.x - 1, p.y) &&
		is_walkable_block(m, p.x + 1, p.y))
		m->door[d]->axis = Axis_X;
	else
		return (error_raise(g, Error_InvalidDoorPlace, NULL));
	m->door[d]->pos = p;
	m->door[d]->doortex = Id_Door1;
	m->door[d]->factor = 1.0;
	m->door[d]->ignore_interact = 0;
	map_set_attr(m, p.x, p.y, d + 1);
	return (TRUE);
}

static t_bool	n_s(t_game *g, t_point p, int s)
{
	t_map		*m;

	m = &g->map;
	if (!(m->secret[s] = ft_calloc(1, sizeof(t_secret))))
		return (error_raise(g, Error_System, "alloc secret failed"));
	if (!(m->secret[s]->look = block_get_secret_look(map_get(m, p.x, p.y))))
		return (error_raise(g, Error_InvalidSecretPlace, NULL));
	m->secret[s]->pos = p;
	m->secret[s]->soundtick = 10;
	map_set_attr(m, p.x, p.y, s + 1);
	return (TRUE);
}

t_bool			map_load_facility(t_game *g, int di, int si)
{
	t_point		p;
	int			c;

	if (!di && !si)
		return (TRUE);
	if (di)
		if (!(g->map.door = ft_calloc(di, sizeof(t_door*))))
			return (error_raise(g, Error_System, "make doors array failed"));
	if (si)
		if (!(g->map.secret = ft_calloc(si, sizeof(t_secret*))))
			return (error_raise(g, Error_System, "make secrets array failed"));
	p.y = -1;
	while (++p.y < g->map.size.height)
	{
		p.x = -1;
		while (++p.x < g->map.size.width)
		{
			c = map_get(&g->map, p.x, p.y);
			if (block_is_door(c) && !n_d(g, p, --di))
				return (FALSE);
			if (block_get_secret_look(c) && !n_s(g, p, --si))
				return (FALSE);
		}
	}
	return (TRUE);
}
