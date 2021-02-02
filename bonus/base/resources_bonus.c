/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:27:17 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 18:57:42 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool		resources_load(t_game *g)
{
	int		i;

	i = 0;
	if (!(g->resource.texs[i++] = texset_empty(g)))
		return (FALSE);
	while (g->map.tex[i])
	{
		if (!(g->resource.texs[i] = texset_new(g, g->map.tex[i])))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void		resources_unload(t_game *g)
{
	int		i;

	i = 0;
	while (g->resource.texs[i])
	{
		texset_delete(g, g->resource.texs[i]);
		g->resource.texs[i++] = NULL;
	}
}

/*
**  Get a color at specified rx, ry from texture
**
**  rx, ry:  they have a ratio value of the maximum width or height
**           of the textures to be 1 * R.
*/

static int	pick_pixel(t_image *img, t_point *texfrac)
{
	int		*addr;
	int		texx;
	int		texy;
	int		color;

	texx = texfrac->x * img->size.width >> RBITS;
	texy = texfrac->y * img->size.height >> RBITS;
	addr = (int*)((img->size_line * texy + (texx << 2)) + img->data_addr);
	color = *addr;
	if ((color & 0xFF000000) == 0xFF000000)
		color = 0;
	return (color);
}

int			resources_pixel_raw(t_texset *tx, int i, t_point *f)
{
	return (pick_pixel(tx->imgs[i], f));
}

int			resources_get_pixel(t_game *g, int id, t_point *texfrac)
{
	return (pick_pixel(texset_get_img(g, id), texfrac));
}
