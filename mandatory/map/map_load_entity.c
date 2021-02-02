/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:43:27 by smun              #+#    #+#             */
/*   Updated: 2021/01/20 18:27:43 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
	if (!(entity = malloc(sizeof(t_entity))))
		return (error_raise(g, Error_System, "try_add_entity failed."));
	if (!(elem = ft_lstnew(entity)))
	{
		free(entity);
		return (error_raise(g, Error_System, "try_add_entity failed."));
	}
	entity_init(g, entity, pt, c);
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
