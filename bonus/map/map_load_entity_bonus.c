/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_entity_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:43:27 by smun              #+#    #+#             */
/*   Updated: 2021/01/28 15:06:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>
#include <stdlib.h>

static t_bool	set_player_start(t_game *g, t_map *m, t_point pt)
{
	if (m->startdir != 0)
		return (error_raise(g, Error_DuplicatedPlayerStart, NULL));
	m->startdir = map_get(m, pt.x, pt.y);
	m->startpos.x = pt.x;
	m->startpos.y = pt.y;
	map_set(m, pt.x, pt.y, 0);
	return (TRUE);
}

static t_bool	try_add_entity(t_game *g, t_list **lst, int i)
{
	int			c;
	t_point		pt;
	t_entity	*entity;
	t_list		*elem;

	pt = point_new(i % g->map.size.width, i / g->map.size.width);
	c = map_get_entity_type(&g->map, pt.x, pt.y);
	if (c == Entity_None)
		return (TRUE);
	else if (c == Entity_Player)
		return (set_player_start(g, &g->map, pt));
	if (!(entity = ft_calloc(1, sizeof(t_entity))))
		return (error_raise(g, Error_System, "try_add_entity failed."));
	if (!(elem = ft_lstnew(entity)))
	{
		free(entity);
		return (error_raise(g, Error_System, "try_add_entity failed."));
	}
	entity_init(g, entity, pt, c);
	if (!map_is(&g->map, pt.x, pt.y, &block_is_sprite))
		map_set(&g->map, pt.x, pt.y, '0');
	ft_lstadd_back(lst, elem);
	return (TRUE);
}

t_bool			map_load_entity(t_game *g)
{
	t_list		*lst;
	int			i;

	lst = NULL;
	i = 0;
	while (i < g->map.size.width * g->map.size.height)
		if (!try_add_entity(g, &lst, i++))
		{
			ft_lstclear(&lst, &free);
			return (FALSE);
		}
	g->map.ent = lst;
	if (g->map.startdir == 0)
		return (error_raise(g, Error_NoPlayerStart, NULL));
	return (TRUE);
}
