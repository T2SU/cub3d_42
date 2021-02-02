/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_real_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:26:41 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 20:55:39 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

double			util_getf(double x)
{
	return (x - floor(x));
}

double			util_distance(t_vector2 v1, t_vector2 v2)
{
	t_vector2	d;

	d.x = v2.x - v1.x;
	d.y = v2.y - v1.y;
	return (sqrt(d.x * d.x + d.y * d.y));
}
