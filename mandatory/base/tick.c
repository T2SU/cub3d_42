/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:51:16 by smun              #+#    #+#             */
/*   Updated: 2021/01/15 02:57:58 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static size_t	calc_tick_rate(t_game *g, int framerate)
{
	double		tickrate;
	double		extent;
	double		unit;

	tickrate = ceil(1.0 / MLX_LOOP_INTERVAL / framerate);
	extent = g->screensize.width * g->screensize.height;
	unit = extent / UNIT_SCREEN_EXTENT;
	return ((size_t)(tickrate / unit / 2.0));
}

void			tick_init(t_game *g)
{
	g->tick.tick_rate = calc_tick_rate(g, TARGET_FRAMERATE);
}

t_bool			tick_update(t_game *g)
{
	if ((g->tick.tick++ % g->tick.tick_rate) == 0)
	{
		return (TRUE);
	}
	return (FALSE);
}
