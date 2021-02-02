/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:43:49 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

t_bool		project_3d(t_game *g)
{
	int			x;
	double		camerax;
	t_vector2	raydir;
	t_raycast	ray;

	x = 0;
	while (x < g->screensize.width)
	{
		camerax = 2 * (x / (double)g->screensize.width) - 1;
		raydir = vec_mult_scalar(g->player.plane, camerax);
		raydir = vec_add(g->player.dir, raydir);
		ray = geometry_raycast(g, g->player.pos, raydir);
		project_wall(g, x, &ray, raydir);
		x++;
	}
	project_sprite(g);
	return (TRUE);
}
