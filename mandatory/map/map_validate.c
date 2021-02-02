/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:29:47 by smun              #+#    #+#             */
/*   Updated: 2021/01/18 22:38:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	validate(t_game *g, t_valmap vm, int m(t_game*, t_point))
{
	vm.in = vm.i;
	while (vm.in.y != vm.max.y)
	{
		vm.mark = -1;
		vm.ij = vm.in;
		while (vm.ij.x != vm.max.x && vm.ij.y != vm.max.y)
		{
			if (block_is_wall(m(g, vm.ij)))
				vm.mark = vm.ij.x;
			if (vm.mark < 0 && !block_is_void(m(g, vm.ij)))
				return (error_raise(g, Error_NotSurroundedByWall, NULL));
			else if (vm.mark > -1 && block_is_void(m(g, vm.ij)))
				if (!map_check_rev(g, vm, m) || !(vm.mark = -1))
					return (FALSE);
			vm.ij.x += vm.d_inner.x;
			vm.ij.y += vm.d_inner.y;
		}
		if (vm.mark > -1 && !map_check_rev(g, vm, m))
			return (FALSE);
		vm.in.x += vm.d_outer.x;
		vm.in.y += vm.d_outer.y;
	}
	return (TRUE);
}

static int		get_map_xy(t_game *g, t_point pt)
{
	return (map_get(&g->map, pt.x, pt.y));
}

static int		get_map_yx(t_game *g, t_point pt)
{
	return (map_get(&g->map, pt.y, pt.x));
}

static t_bool	validate_diag(t_game *g, t_map *m)
{
	t_valmap	vm;

	vm.d_outer = point_new(0, 1);
	vm.d_inner = point_new(1, 1);
	vm.i = point_new(0, 0);
	vm.max = point_new(m->size.width, m->size.height);
	if (!validate(g, vm, &get_map_xy))
		return (FALSE);
	vm.max = point_new(m->size.height, m->size.width);
	if (!validate(g, vm, &get_map_yx))
		return (FALSE);
	vm.d_inner = point_new(-1, 1);
	vm.i = point_new(m->size.width - 1, 0);
	vm.max = point_new(-1, m->size.height);
	if (!validate(g, vm, &get_map_xy))
		return (FALSE);
	vm.i = point_new(m->size.height - 1, 0);
	vm.max = point_new(-1, m->size.width);
	if (!validate(g, vm, &get_map_yx))
		return (FALSE);
	return (TRUE);
}

t_bool			map_validate(t_game *g, t_map *m)
{
	t_valmap	vm;

	vm.i = point_new(0, 0);
	vm.d_inner = point_new(1, 0);
	vm.d_outer = point_new(0, 1);
	vm.max = point_new(m->size.width, m->size.height);
	if (!validate(g, vm, &get_map_xy))
		return (FALSE);
	vm.max = point_new(m->size.height, m->size.width);
	if (!validate(g, vm, &get_map_yx))
		return (FALSE);
	return (validate_diag(g, m));
}
