/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texset_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:33:02 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 18:00:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_image			*texset_get_img(t_game *g, int id)
{
	t_texset	*tex;

	if (!id)
		return (NULL);
	tex = g->resource.texs[id];
	return (tex->imgs[tex->i]);
}

void			texset_nextframe(t_game *g, int id, t_bool loop)
{
	t_texset	*tex;

	tex = g->resource.texs[id];
	if (loop || tex->i + 1 < tex->imgcnt)
		tex->i = (tex->i + 1) % tex->imgcnt;
}

void			texset_resetframe(t_game *g, int id)
{
	t_texset	*tex;

	tex = g->resource.texs[id];
	tex->i = 0;
}

void			texset_update(t_game *g)
{
	texset_nextframe(g, Id_Sprite1, TRUE);
	texset_nextframe(g, Id_Sprite2, TRUE);
}
