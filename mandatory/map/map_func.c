/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:14:28 by smun              #+#    #+#             */
/*   Updated: 2021/01/18 22:38:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_get(t_map *m, int x, int y)
{
	return (m->field[y * m->size.width + x]);
}

void	map_set(t_map *m, int x, int y, int c)
{
	m->field[y * m->size.width + x] = c;
}

t_bool	map_check_rev(t_game *g, t_valmap vm, int m(t_game*, t_point))
{
	while ((vm.ij.x -= vm.d_inner.x) > vm.mark)
	{
		vm.ij.y -= vm.d_inner.y;
		if (block_is_walkable(m(g, vm.ij)))
			return (error_raise(g, Error_NotSurroundedByWall, NULL));
	}
	return (TRUE);
}
