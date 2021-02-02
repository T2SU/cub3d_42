/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 01:41:18 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:39 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
