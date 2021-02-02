/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   facility_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:15:34 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:42:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

static t_bool	check_in_rect(t_point pt, t_entity *e, double scale)
{
	t_rect		rc_fac;
	t_rect		rc;

	rc_fac.left = pt.x;
	rc_fac.top = pt.y;
	rc_fac.width = 1;
	rc_fac.height = 1;
	rc = rect_from_size(e->pos, vec_mult_scalar(e->size, scale));
	return (rect_overlaps(rc_fac, rc));
}

t_bool			facility_can_interact(t_point pt, t_entity *e)
{
	return (check_in_rect(pt, e, 2.0));
}

t_bool			facility_is_in_someone(t_game *g, t_point pt)
{
	t_list		*lst;
	t_entity	*e;

	if (check_in_rect(pt, &g->player, 1.1))
		return (TRUE);
	lst = g->map.ent;
	while (lst)
	{
		e = (t_entity*)lst->content;
		if (entity_is_life(e->type) && e->hp > 0)
			if (check_in_rect(pt, e, 1.1))
				return (TRUE);
		lst = lst->next;
	}
	return (FALSE);
}

void			facility_update(t_game *g)
{
	int			i;

	i = 0;
	while (i < g->map.doorcnt)
		door_update(g, g->map.door[i++]);
	i = 0;
	while (i < g->map.secretcnt)
		secret_update(g, g->map.secret[i++]);
}
