/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:51:48 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_bool			map_is_wall(t_map *m, int x, int y)
{
	if (y < 0 || y >= m->size.height || x < 0 || x >= m->size.width)
		return (TRUE);
	return (block_is_wall(map_get(m, x, y)));
}

int				map_get_entity_type(t_map *m, int x, int y)
{
	int			block;

	if (y < 0 || y >= m->size.height || x < 0 || x >= m->size.width)
		return (TRUE);
	block = map_get(m, x, y);
	if (block_is_item(block))
		return (Entity_Medikit);
	else if (block == 'S' || block == 'W' || block == 'E' || block == 'N')
		return (Entity_Player);
	return (Entity_None);
}

t_vector2		map_alter_movevec(t_map *m, t_entity *e, t_vector2 mv)
{
	double		s;
	t_vector2	d;
	t_vector2	pos;
	t_vector2	sz;
	t_vector2	nmv;

	pos = e->pos;
	s = e->move_speed;
	sz = e->size;
	d = vec_new(util_sign(mv.x), util_sign(mv.y));
	nmv.x = pos.x + d.x * (s + (sz.x / 2));
	nmv.y = pos.y + d.y * (s + (sz.y / 2));
	if (map_is_wall(m, (int)nmv.x, (int)(pos.y - (sz.y / 2))))
		mv.x = 0;
	else if (map_is_wall(m, (int)nmv.x, (int)(pos.y + (sz.y / 2))))
		mv.x = 0;
	if (map_is_wall(m, (int)(pos.x - (sz.x / 2)), (int)nmv.y))
		mv.y = 0;
	else if (map_is_wall(m, (int)(pos.x + (sz.x / 2)), (int)nmv.y))
		mv.y = 0;
	return (mv);
}

int				map_get_wall_texid(t_game *g, int x, int y, int orient)
{
	if (y < 0 || y >= g->map.size.height ||
		x < 0 || x >= g->map.size.width)
		return (0);
	if (orient == 'N')
		return (Id_TextureN);
	if (orient == 'S')
		return (Id_TextureS);
	if (orient == 'E')
		return (Id_TextureE);
	if (orient == 'W')
		return (Id_TextureW);
	return (Id_Null);
}
