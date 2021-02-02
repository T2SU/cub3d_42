/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_life_appearance_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:50:14 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 03:23:45 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int				entity_life_pixel(t_game *g, t_entity *e, int i, t_point *fr)
{
	t_texset	*tex;

	tex = g->resource.texs[e->life.texid[e->life.state]];
	if (!entity_life_is_oriented_state(e->life.state))
		return (resources_pixel_raw(tex, e->life.i, fr));
	return (resources_pixel_raw(tex, i, fr));
}

int				entity_life_curframe(t_game *g, t_entity *e, t_spriteview *sv)
{
	int			i;

	sv->vieworient = entity_get_view_orient(e, &g->player);
	i = e->life.i * e->life.orientnum;
	if (sv->vieworient == Orient_S)
		i += 0;
	else if (sv->vieworient == Orient_SW)
		i += 1;
	else if (sv->vieworient == Orient_W)
		i += 2;
	else if (sv->vieworient == Orient_NW)
		i += 3;
	else if (sv->vieworient == Orient_N)
		i += 4;
	else if (sv->vieworient == Orient_SE)
		i += (e->life.orientnum == 5 ? 1 : 7);
	else if (sv->vieworient == Orient_E)
		i += (e->life.orientnum == 5 ? 2 : 6);
	else if (sv->vieworient == Orient_NE)
		i += (e->life.orientnum == 5 ? 3 : 5);
	return (i);
}
