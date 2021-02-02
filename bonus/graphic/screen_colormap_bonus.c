/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_colormap_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:03:47 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:44:17 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

void			screen_setcolormap(t_game *g, int color, size_t dur)
{
	t_uchar		*clr;

	clr = (t_uchar*)(&color);
	g->colormap[0] = clr[0];
	g->colormap[1] = clr[1];
	g->colormap[2] = clr[2];
	g->colormapdur = dur;
}

void			screen_apply_colormap(t_game *g)
{
	t_image		*scr;
	t_point		pt;
	t_uchar		*color;

	scr = g->screen;
	pt.y = -1;
	while (++pt.y < g->screensize.height)
	{
		color = (t_uchar*)scr->data_addr + pt.y * scr->size_line;
		pt.x = -1;
		while (++pt.x < g->screensize.width)
		{
			color[0] = (t_uchar)ft_min(255, color[0] + g->colormap[0]);
			color[1] = (t_uchar)ft_min(255, color[1] + g->colormap[1]);
			color[2] = (t_uchar)ft_min(255, color[2] + g->colormap[2]);
			color += 4;
		}
	}
	g->colormapdur--;
	if (g->colormapdur == 0)
		ft_bzero(g->colormap, sizeof(g->colormap));
}
