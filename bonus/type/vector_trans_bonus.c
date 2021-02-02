/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_trans_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 01:41:18 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:39:14 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

t_vector2		vec_rotraw(t_vector2 *o, t_vector2 *uv)
{
	t_vector2	vec;

	vec.x = o->x * uv->x - o->y * uv->y;
	vec.y = o->x * uv->y + o->y * uv->x;
	return (vec);
}

/*
**  Trigonometry addition theorem
**  + vector rotation transformation
**  ref: https://blog.naver.com/dalsapcho/20144939371
*/

t_vector2		vec_rot(t_vector2 o, double theta)
{
	t_vector2	uv;

	uv.y = sin(theta);
	uv.x = cos(theta);
	return (vec_rotraw(&o, &uv));
}

/*
**  get coordinate from frstrum by multiply view matrix
**  ref: https://showmiso.tistory.com/146
**       https://lodev.org/cgtutor/raycasting3.html
**       https://www.gpgstudy.com/forum/viewtopic.php?t=1891
**
**   [  d.y*rl.x - d.x*rl.y ]
**   [                      ] * (pl.x * d.y - d.x * pl.y)^-1
**   [-pl.y*rl.x + pl.x*rl.y]
**
**  Perform multiply vector to dest(rl) with 2x2 camera matrix inverse.(above)
*/

t_vector2		vec_cam(t_vector2 rl, t_vector2 pl, t_vector2 d)
{
	t_vector2	res;
	double		div;

	div = pl.x * d.y - d.x * pl.y;
	res.x = (d.y * rl.x - d.x * rl.y) / div;
	res.y = (-pl.y * rl.x + pl.x * rl.y) / div;
	return (res);
}
