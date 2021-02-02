/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_architect_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:20:05 by smun              #+#    #+#             */
/*   Updated: 2021/01/27 17:41:57 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool			map_is_walkable(t_map *m, int x, int y)
{
	if (map_is(m, x, y, &block_is_wall))
		return (FALSE);
	else if (map_is(m, x, y, &block_is_void))
		return (FALSE);
	else if (map_is(m, x, y, &block_is_sprite))
		return (FALSE);
	else if (map_is(m, x, y, &block_is_door))
		return (door_is_throughable(m, x, y));
	else if (map_is(m, x, y, &block_get_secret_look))
		return (secret_is_throughable(m, x, y));
	return (TRUE);
}

t_bool			map_is(t_map *m, int x, int y, t_bool (p(int)))
{
	if (y < 0 || y >= m->size.height || x < 0 || x >= m->size.width)
		return (TRUE);
	return (p(map_get(m, x, y)) != 0);
}
