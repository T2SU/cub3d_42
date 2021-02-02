/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:27:17 by smun              #+#    #+#             */
/*   Updated: 2021/01/15 19:35:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool			resources_load(t_game *g)
{
	int			i;

	i = 0;
	if (!(g->resource.imgs[i++] = image_new(g, size_new(16, 16))))
		return (FALSE);
	while (g->map.tex[i])
	{
		if (!(g->resource.imgs[i] = image_load(g, g->map.tex[i])))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void			resources_unload(t_game *g)
{
	int			i;

	i = 0;
	while (g->resource.imgs[i])
	{
		image_unload(g, g->resource.imgs[i]);
		g->resource.imgs[i++] = NULL;
	}
}

/*
**  Get a color at specified rx, ry from texture
**
**  rx, ry:  they have a ratio value of the maximum width or height
**           of the textures to be 1 * R.
*/

int				resources_get_pixel(t_game *g, int id, t_point texfrac)
{
	int			texx;
	int			texy;
	t_image		*wall;
	size_t		px;

	wall = g->resource.imgs[id];
	texx = texfrac.x * wall->size.width / R;
	texy = texfrac.y * wall->size.height / R;
	px = wall->bytes_per_pixel;
	if (px == sizeof(int))
		return (*(int*)&wall->data_addr[wall->size_line * texy + texx * px]);
	ft_memcpy(&px, &wall->data_addr[wall->size_line * texy + texx * px], px);
	return (px);
}
