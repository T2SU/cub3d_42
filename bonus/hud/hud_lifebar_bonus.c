/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_lifebar_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 01:23:42 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 06:28:44 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		calc_gauge_offset(t_game *g, int width)
{
	int			px;
	t_image		*bar;

	bar = texset_get_img(g, hud_to_resid(g, Hud_Lifebar));
	px = (int)(75 * width / (double)bar->size.width);
	return (px);
}

static void		draw_gauge(t_game *g, t_point pos, t_size sz, int r)
{
	t_point		pt;
	t_point		frac;
	int			color;
	int			tex;
	int			width;

	tex = hud_to_resid(g, Hud_LifeGauge);
	pt.x = pos.x - 1;
	width = (sz.width * r) >> RBITS;
	while (++pt.x < pos.x + width)
	{
		frac.x = R * (pt.x - pos.x) / (sz.width);
		pt.y = pos.y - 1;
		while (++pt.y < pos.y + sz.height)
		{
			frac.y = R * (pt.y - pos.y) / (sz.height);
			color = resources_get_pixel(g, tex, &frac);
			if (color & 0xffffff)
				draw_pixel(g, pt.x, pt.y, color);
		}
	}
}

static t_entity	*get_current_attention(t_game *g)
{
	t_entity	*e;

	if (!(e = g->attention))
		return (NULL);
	if (e->hp == 0)
	{
		if (!g->attentiondur)
			g->attention = NULL;
		else
			g->attentiondur--;
	}
	else
	{
		g->attentiondur = 50;
	}
	return (e);
}

void			hud_draw_lifebar(t_game *g)
{
	static int	gaugeoffset;
	t_point		offset;
	t_size		size;
	t_entity	*e;

	if (!(e = get_current_attention(g)))
		return ;
	offset = hud_offset(g, Hud_Lifebar);
	size = hud_size(g, Hud_Lifebar);
	hud_put(g, offset, size, hud_to_resid(g, Hud_Lifebar));
	if (!gaugeoffset)
		gaugeoffset = calc_gauge_offset(g, size.width);
	offset.x += gaugeoffset;
	size = hud_size(g, Hud_LifeGauge);
	draw_gauge(g, offset, size, e->hp * R / e->maxhp);
}
