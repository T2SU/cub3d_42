/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:00:42 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point			point_from_vector(t_vector2 vec)
{
	return (point_new((int)vec.x, (int)vec.y));
}

t_point			point_new(int x, int y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	return (p);
}

t_vector2		point_to_vector(t_point pt)
{
	return (vec_new(pt.x, pt.y));
}
