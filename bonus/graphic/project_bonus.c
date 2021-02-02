/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:43:49 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:43:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool			project_3d(t_game *g)
{
	int			x;
	double		camerax;
	t_vector2	raydir;
	t_raycast	ray;

	project_skybox(g, g->player.dir);
	x = 0;
	while (x < g->screensize.width)
	{
		camerax = 2 * (x / (double)g->screensize.width) - 1;
		raydir.x = g->player.dir.x + g->player.plane.x * camerax;
		raydir.y = g->player.dir.y + g->player.plane.y * camerax;
		ray = geometry_raycast(g, g->player.pos, raydir, Raycast_Default);
		project_wall(g, x, &ray, raydir);
		x++;
	}
	project_sprite(g);
	return (TRUE);
}
