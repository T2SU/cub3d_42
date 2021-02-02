/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_digit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:40:53 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 02:02:51 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

/*
**  https://stackoverflow.com/questions/1414215
**  Hardcoded offset for './ui/digit.png'
*/

static int		get_digit_size(int num, int axis)
{
	static int	width[10];
	static int	height[10];
	int			i;

	if (!height[0])
	{
		i = 0;
		while (i < 10)
		{
			if (i == 1)
				width[i] = 14;
			else
				width[i] = 24;
			width[i] = width[i];
			height[i] = 32;
			i++;
		}
	}
	return ((axis == Axis_X ? width : height)[num]);
}

static int		get_number_offset(int num)
{
	static int	cached[10];
	int			i;
	int			offset;

	if (num == 0 || cached[num])
		return (cached[num]);
	offset = 0;
	i = 0;
	while (i < num)
		offset += get_digit_size(i++, Axis_X);
	if (num > 0)
		offset++;
	return (cached[num] = offset);
}

static void		draw_digit(t_game *g, t_point *pos, int digit)
{
	int			atlaswidth;
	t_size		sz;
	t_point		idx;
	int			color;
	t_point		frac;

	atlaswidth = texset_get_img(g, Id_Digit)->size.width;
	atlaswidth = (int)(atlaswidth * hud_scale(g, Hud_Digit));
	sz.width = (int)(get_digit_size(digit, Axis_X) * hud_scale(g, Hud_Digit));
	sz.height = (int)(get_digit_size(digit, Axis_Y) * hud_scale(g, Hud_Digit));
	idx.x = -1;
	while (++idx.x < sz.width)
	{
		frac.x = get_number_offset(digit);
		frac.x = (idx.x + frac.x * hud_scale(g, Hud_Digit)) * R / atlaswidth;
		idx.y = -1;
		while (++idx.y < sz.height)
		{
			frac.y = R * idx.y / sz.height;
			color = resources_get_pixel(g, Id_Digit, &frac);
			if (color & 0xffffff)
				draw_pixel(g, pos->x + idx.x, pos->y + idx.y, color);
		}
	}
	pos->x += sz.width;
}

void			hud_draw_digit(t_game *g, t_point pos, int number)
{
	long		nbr;
	long		digits;
	long		div;
	long		n;

	digits = 1;
	nbr = number;
	if (nbr < 0)
		nbr = 0;
	if (nbr)
		digits = ((long)log10(nbr)) + 1;
	div = (long)pow(10, digits - 1);
	while (digits-- > 0)
	{
		n = nbr / div;
		nbr = (nbr % div) * 10;
		draw_digit(g, &pos, n);
	}
}
