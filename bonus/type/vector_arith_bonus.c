/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arith_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 01:41:18 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 04:49:54 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

t_vector2		vec_add(t_vector2 vec, t_vector2 d)
{
	vec.x += d.x;
	vec.y += d.y;
	return (vec);
}

t_vector2		vec_mult(t_vector2 vec, t_vector2 d)
{
	vec.x *= d.x;
	vec.y *= d.y;
	return (vec);
}

t_vector2		vec_mult_scalar(t_vector2 vec, double d)
{
	vec.x *= d;
	vec.y *= d;
	return (vec);
}

t_vector2		vec_sub(t_vector2 vec, t_vector2 d)
{
	vec.x -= d.x;
	vec.y -= d.y;
	return (vec);
}

t_vector2		vec_norm(t_vector2 vec)
{
	double		r;

	r = sqrt(vec.x * vec.x + vec.y * vec.y);
	vec.x /= r;
	vec.y /= r;
	return (vec);
}
