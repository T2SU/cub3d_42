/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_const.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 00:27:28 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 16:38:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector2		entity_get_size(int type)
{
	if (type == Entity_Player)
		return (vec_new(0.3, 0.3));
	else if (type == Entity_Medikit)
		return (vec_new(0.5, 0.5));
	return (vec_new(0, 0));
}

t_vector2		entity_get_scale(int type)
{
	if (type == Entity_Medikit)
		return (vec_new(0.30, 0.2));
	return (vec_new(1.0, 1.0));
}

double			entity_get_yoffset(int type)
{
	if (type == Entity_Medikit)
		return (0.4);
	return (0.0);
}

int				entity_get_texid(t_entity *e)
{
	if (e->type == Entity_Medikit)
		return (Id_Sprite);
	return (Id_Null);
}
