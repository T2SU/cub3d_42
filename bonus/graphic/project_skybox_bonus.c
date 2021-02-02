/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_skybox_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:16:16 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:43:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

/*
**  ==[[ Note for rendering a Skybox ]]==
**
** 0 degree ~ 360 degree
** -->
** 0  ~  1
**
** 360 degree = 90(an one side of direction) * 4
** skybox 1 pixel = 1 / 4 * (screen width)
**
** tex x frac offset =  angle / 360 degree
**                      angle(rad) / 2PI
** skybox loop = RATIO
**
** loop with tex x frac offset = (angle * RATIO / 2PI) + 0.5 * RATIO
*/

t_bool		project_skybox(t_game *g, t_vector2 dir)
{
	double	angle;
	int		offset;
	t_point	texfrac;
	t_point	pt;
	int		color;

	angle = atan2(dir.y, dir.x);
	offset = (int)(angle * R * SKYBOX_RATIO / (M_PI * 2)) + R_2 * SKYBOX_RATIO;
	pt.y = 0;
	while (pt.y < g->screensize.height / 2)
	{
		texfrac.y = pt.y * 2 * R / g->screensize.height;
		pt.x = 0;
		while (pt.x < g->screensize.width)
		{
			texfrac.x = pt.x * R / (4 * g->screensize.width / SKYBOX_RATIO);
			texfrac.x = (texfrac.x + offset) % R;
			color = resources_get_pixel(g, Id_Skybox, &texfrac);
			draw_pixel(g, pt.x, pt.y, color);
			pt.x++;
		}
		pt.y++;
	}
	return (TRUE);
}
