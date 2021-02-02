/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_wall_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:56:48 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:43:50 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>
#include <math.h>

/*
**  min_raydir = player.dir - player.plane
**  draw_dir = min_raydir + 2 * player.plane * (x / screenwidth)
**  floorpos = draw_dir * distance + player.pos  (World Coordinate)
*/

static void		draw_floor_tex(t_game *g, t_point *pt, int h, t_vector2 *ddir)
{
	double		distance;
	int			color;
	t_point		texfrac;
	double		fposx;
	double		fposy;

	distance = (double)h / (pt->y - h);
	fposx = ddir->x * distance;
	fposy = ddir->y * distance;
	distance = sqrt(fposx * fposx + fposy * fposy);
	fposx += g->player.pos.x;
	fposy += g->player.pos.y;
	texfrac.x = (int)(R * util_getf(fposx)) % R;
	texfrac.y = (int)(R * util_getf(fposy)) % R;
	color = resources_get_pixel(g, Id_Floor, &texfrac);
	color = geometry_shade(distance, color);
	draw_pixel(g, pt->x, pt->y, color);
}

static void		draw_floor(t_game *g, int x, int wh)
{
	int			h;
	t_point		pt;
	int			ymax;
	t_vector2	ddir;
	t_vector2	rd0;

	h = g->screensize.height / 2;
	pt = point_new(x, ft_max(0, h + wh - 1));
	ymax = 2 * h - 1;
	rd0.x = g->player.dir.x - g->player.plane.x;
	rd0.y = g->player.dir.y - g->player.plane.y;
	ddir.x = rd0.x + g->player.plane.x * 2 * x / g->screensize.width;
	ddir.y = rd0.y + g->player.plane.y * 2 * x / g->screensize.width;
	while (++pt.y < ymax)
		draw_floor_tex(g, &pt, h, &ddir);
}

static int		get_distanced_color(t_game *g, int id, int x, t_point *texfrac)
{
	int			color;
	double		z;

	color = resources_get_pixel(g, id, texfrac);
	z = g->z[x];
	return (geometry_shade(z, color));
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
	texid = map_get_wall_texid(g, r->mappos.x, r->mappos.y);
	y = ft_max(0, h - wh);
	while (y < g->screensize.height - 1 && y < h + wh)
	{
		texfrac.y = (y - (h - wh)) * R / (2 * wh);
		draw_pixel(g, x, y, get_distanced_color(g, texid, x, &texfrac));
		y++;
	}
	draw_floor(g, x, wh);
}
