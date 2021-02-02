/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:56:48 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 17:49:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void		draw_ceil_floor(t_game *g, int x, int wh, int mode)
{
	int			h;
	int			y;
	int			ymax;
	int			color;

	h = g->screensize.height / 2;
	if (mode == Draw_Ceiling)
	{
		y = 0;
		ymax = h - wh;
		color = g->map.color_ceil;
	}
	else
	{
		y = h + wh;
		ymax = 2 * h - 1;
		color = g->map.color_floor;
	}
	while (y < ymax)
	{
		draw_pixel(g, x, y, color);
		y++;
	}
}

void			project_wall(t_game *g, int x, t_raycast *r, t_vector2 rd)
{
	t_point		texfrac;
	int			h;
	int			wh;
	int			texid;
	int			y;

	h = g->screensize.height / 2;
	g->z[x] = geometry_get_orthodist(g, r, rd);
	if ((wh = (int)(h / g->z[x])) <= 0)
		return ;
	texfrac.x = (int)(geometry_correct(r, rd) * R);
	texid = map_get_wall_texid(g, r->mappos.x, r->mappos.y, r->orient);
	draw_ceil_floor(g, x, wh, Draw_Ceiling);
	y = ft_max(0, h - wh);
	while (y < g->screensize.height - 1 && y < h + wh)
	{
		texfrac.y = (y - (h - wh)) * R / (2 * wh);
		draw_pixel(g, x, y, resources_get_pixel(g, texid, texfrac));
		y++;
	}
	draw_ceil_floor(g, x, wh, Draw_Floor);
}
