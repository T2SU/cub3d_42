/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_func_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:14:28 by smun              #+#    #+#             */
/*   Updated: 2021/01/20 13:56:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		map_get_attr(t_map *m, int x, int y)
{
	return ((m->field[y * m->size.width + x] >> 8) & 0xffffff);
}

void	map_set_attr(t_map *m, int x, int y, int attr)
{
	attr = ((attr & 0xffffff) << 8) | map_get(m, x, y);
	m->field[y * m->size.width + x] = attr;
}

int		map_get(t_map *m, int x, int y)
{
	return (m->field[y * m->size.width + x] & 0xFF);
}

void	map_set(t_map *m, int x, int y, int c)
{
	m->field[y * m->size.width + x] = c & 0xFF;
}

t_bool	map_check_rev(t_game *g, t_valmap vm, int m(t_game*, t_point))
{
	while ((vm.ij.x -= vm.d_inner.x) > vm.mark)
	{
		vm.ij.y -= vm.d_inner.y;
		if (!block_is_void(m(g, vm.ij)) && !block_is_wall(m(g, vm.ij)))
			return (error_raise(g, Error_NotSurroundedByWall, NULL));
	}
	return (TRUE);
}
