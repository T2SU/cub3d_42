/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:51:16 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:39:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static size_t	calc_tick_rate(t_game *g)
{
	double		extent;
	double		unit;

	extent = g->screensize.width * g->screensize.height;
	unit = UNIT_SCREEN_EXTENT / extent;
	return ((size_t)(fmax(2, unit)));
}

void			tick_init(t_game *g)
{
	g->tick.tick_rate = calc_tick_rate(g);
}

t_bool			tick_update(t_game *g)
{
	g->tick.tick++;
	if (!g->hidemouse)
		return (FALSE);
	if ((g->tick.tick % g->tick.tick_rate) == 0)
	{
		g->tick.loopcnt++;
		return (TRUE);
	}
	return (FALSE);
}
