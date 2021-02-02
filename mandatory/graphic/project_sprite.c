/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:01:16 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:39:14 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>

static void			draw_sprite(t_game *g, t_entity *e, t_spriteview *sv)
{
	t_point			pt;
	t_point			texfrac;
	int				color;

	pt.x = sv->rend.x;
	while (--pt.x >= sv->rstart.x)
	{
		if (sv->coord.y >= g->z[pt.x])
			continue ;
		pt.y = sv->rend.y;
		while (--pt.y >= sv->rstart.y)
		{
			texfrac.x = sv->size.width - (sv->end.x - pt.x);
			texfrac.y = sv->size.height - (sv->end.y - pt.y);
			texfrac.x = R * texfrac.x / sv->size.width;
			texfrac.y = R * texfrac.y / sv->size.height;
			color = resources_get_pixel(g, entity_get_texid(e), texfrac);
			if (color & 0xffffff)
				draw_pixel(g, pt.x, pt.y, color);
		}
	}
}

/*
**  https://devbot.tistory.com/entry/%ED%96%89%EB%A0%AC
**  https://lalyns.tistory.com/13
*/

static void			project_sprite_on_view(t_game *g, t_entity *e)
{
	t_spriteview	sv;
	t_size			scr;

	sv.coord = vec_sub(e->pos, g->player.pos);
	sv.coord = vec_cam(sv.coord, g->player.plane, g->player.dir);
	if (sv.coord.y <= 0)
		return ;
	scr = g->screensize;
	sv.yoffset = (int)(e->yoffset / sv.coord.y);
	sv.size.width = (int)fabs(scr.height / sv.coord.y / e->scale.x);
	sv.size.height = (int)fabs(scr.height / sv.coord.y / e->scale.y);
	sv.start.x = (int)((scr.width / 2) * (1 + sv.coord.x / sv.coord.y));
	sv.start.y = (int)(scr.height / 2 + sv.yoffset);
	sv.start.x -= sv.size.width / 2;
	sv.start.y -= sv.size.height / 2;
	sv.end.x = sv.start.x + sv.size.width;
	sv.end.y = sv.start.y + sv.size.height;
	sv.rstart = point_new(ft_max(0, sv.start.x), ft_max(0, sv.start.y));
	sv.rend.x = ft_min(sv.end.x, scr.width - 1);
	sv.rend.y = ft_min(sv.end.y, scr.height - 1);
	draw_sprite(g, e, &sv);
}

static void			fill_entities(t_game *g, t_fpair *ents)
{
	t_vector2		dv;
	t_list			*cur;

	cur = g->map.ent;
	while (cur)
	{
		ents->p = cur->content;
		dv = vec_sub(((t_entity*)cur->content)->pos, g->player.pos);
		ents->f = dv.x * dv.x + dv.y + dv.y;
		cur = cur->next;
		ents++;
	}
}

t_bool				project_sprite(t_game *g)
{
	t_fpair			*ents;
	int				size;

	size = ft_lstsize(g->map.ent);
	if (!(ents = malloc(sizeof(t_fpair) * size)))
		return (error_raise(g, Error_System, "failed on project_sprite"));
	fill_entities(g, ents);
	util_qsort(&ents, size);
	while (size-- > 0)
		project_sprite_on_view(g, (t_entity*)(ents[size].p));
	free(ents);
	return (TRUE);
}
