/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:51:48 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 04:23:21 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static int		map_get_entity_type2(int block)
{
	if (block == 'B')
		return (Entity_Sprite1);
	else if (block == 'C')
		return (Entity_Sprite2);
	else if (block == 'L')
		return (Entity_Sprite3);
	else if (block == 'P')
		return (Entity_Sprite4);
	return (Entity_None);
}

int				map_get_entity_type(t_map *m, int x, int y)
{
	int			block;

	if (y < 0 || y >= m->size.height || x < 0 || x >= m->size.width)
		return (TRUE);
	block = map_get(m, x, y);
	if (block == 'M')
		return (Entity_Medikit);
	else if (block == 'm')
		return (Entity_Money);
	else if (block == 'S' || block == 'W' || block == 'E' || block == 'N')
		return (Entity_Player);
	else if (block == 's' || block == 'w' || block == 'e' || block == 'n')
		return (Entity_Enemy1);
	else if (block == 'X')
		return (Entity_Enemy2);
	else if (block == 'A')
		return (Entity_Shell);
	else if (block == 'a')
		return (Entity_Bullet);
	else if (block == 'G')
		return (Entity_Shotgun);
	return (map_get_entity_type2(block));
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
	if (!map_is_walkable(m, (int)nmv.x, (int)(pos.y - (sz.y / 2))))
		mv.x = 0;
	else if (!map_is_walkable(m, (int)nmv.x, (int)(pos.y + (sz.y / 2))))
		mv.x = 0;
	if (!map_is_walkable(m, (int)(pos.x - (sz.x / 2)), (int)nmv.y))
		mv.y = 0;
	else if (!map_is_walkable(m, (int)(pos.x + (sz.x / 2)), (int)nmv.y))
		mv.y = 0;
	return (mv);
}

int				map_get_wall_texid(t_game *g, int x, int y)
{
	t_door		*d;
	t_secret	*s;
	int			c;

	if (y < 0 || y >= g->map.size.height ||
		x < 0 || x >= g->map.size.width)
		return (0);
	c = map_get(&g->map, x, y);
	if (block_is_door(c) && (d = door_get(&g->map, x, y)))
		return (c == 'D' ? Id_Door1 : Id_Door2);
	if (block_get_secret_look(c) && (s = secret_get(&g->map, x, y)))
		c = s->look;
	if (c >= '1' && c <= '9')
		return (Id_Wall1 + (c - '1'));
	return (Id_Null);
}
