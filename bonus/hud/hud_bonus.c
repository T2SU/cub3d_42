/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:15:39 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 06:28:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

void		hud_put(t_game *g, t_point pos, t_size sz, int tex)
{
	t_point	pt;
	t_point	frac;
	int		color;

	pt.x = pos.x - 1;
	while (++pt.x < pos.x + sz.width)
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

t_point		hud_middle_offset(t_game *g, t_point off, t_size sz, int type)
{
	int		yoffset;

	yoffset = texset_get_img(g, hud_to_resid(g, type))->size.height;
	yoffset = (sz.height - (yoffset * hud_scale(g, type))) / 2;
	yoffset = ft_max(0, yoffset);
	off.x += (int)(g->screensize.width * 0.015) + sz.width;
	off.y += yoffset;
	return (off);
}

t_bool		hud_draw(t_game *g)
{
	t_size	sz;
	t_point	pt;

	hud_draw_weapon(g);
	sz = hud_size(g, Hud_Score);
	pt = hud_offset(g, Hud_Score);
	hud_put(g, pt, sz, hud_to_resid(g, Hud_Score));
	hud_draw_digit(g, hud_middle_offset(g, pt, sz, Hud_Digit), g->score);
	sz = hud_size(g, Hud_Hp);
	pt = hud_offset(g, Hud_Hp);
	hud_put(g, pt, sz, hud_to_resid(g, Hud_Hp));
	hud_draw_digit(g, hud_middle_offset(g, pt, sz, Hud_Digit), g->player.hp);
	if (g->gameover != GameOver_None)
	{
		pt = hud_offset(g, Hud_GameOver);
		sz = hud_size(g, Hud_GameOver);
		hud_put(g, pt, sz, hud_to_resid(g, Hud_GameOver));
	}
	hud_draw_lifebar(g);
	return (TRUE);
}
