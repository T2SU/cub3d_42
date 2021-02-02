/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_sprite_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:01:16 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:43:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>
#include <libft.h>
#include <stdlib.h>

static int			get_pixel(t_game *g, t_entity *e, int i, t_spriteview *sv)
{
	int				texid;
	int				color;

	if (!entity_is_life(e->type))
	{
		texid = entity_get_texid(e);
		color = resources_get_pixel(g, texid, &sv->texfrac);
	}
	else
	{
		if (e->life.orientnum == 5)
			if (sv->vieworient == Orient_E || sv->vieworient == Orient_NE ||
				sv->vieworient == Orient_SE)
				if (entity_life_is_oriented_state(e->life.state))
					sv->texfrac.x = R - sv->texfrac.x;
		color = entity_life_pixel(g, e, i, &sv->texfrac);
	}
	return (color);
}

static void			draw_sprite(t_game *g, t_fpair *ef, t_spriteview *sv)
{
	t_point			pt;
	int				color;
	int				i;

	i = entity_life_curframe(g, (t_entity*)ef->p, sv);
	pt.x = sv->rend.x;
	while (--pt.x >= sv->rstart.x)
	{
		if (sv->coord.y >= g->z[pt.x])
			continue ;
		pt.y = sv->rend.y;
		while (--pt.y >= sv->rstart.y)
		{
			sv->texfrac.x = sv->size.width - (sv->end.x - pt.x);
			sv->texfrac.y = sv->size.height - (sv->end.y - pt.y);
			sv->texfrac.x = R * sv->texfrac.x / sv->size.width;
			sv->texfrac.y = R * sv->texfrac.y / sv->size.height;
			color = get_pixel(g, (t_entity*)ef->p, i, sv);
			if (color & 0xffffff)
				draw_pixel(g, pt.x, pt.y, geometry_shade(ef->f, color));
		}
	}
}

/*
**  https://devbot.tistory.com/entry/%ED%96%89%EB%A0%AC
**  https://lalyns.tistory.com/13
*/

static void			project_sprite_on_view(t_game *g, t_fpair *ef)
{
	t_spriteview	sv;
	t_size			scr;
	t_entity		*e;

	e = ef->p;
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
	draw_sprite(g, ef, &sv);
}

static void			fill_entities(t_game *g, t_fpair *ents)
{
	t_vector2		pos;
	t_vector2		epos;
	t_list			*cur;

	pos = g->player.pos;
	cur = g->map.ent;
	while (cur)
	{
		ents->p = cur->content;
		epos = ((t_entity*)cur->content)->pos;
		ents->f = (epos.x - pos.x) * (epos.x - pos.x);
		ents->f += (epos.y - pos.y) * (epos.y - pos.y);
		ents->f = sqrt(ents->f);
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
		project_sprite_on_view(g, &ents[size]);
	free(ents);
	return (TRUE);
}
