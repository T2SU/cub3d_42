/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_const_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 00:27:28 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:40:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector2		entity_get_size(int type)
{
	if (type == Entity_Player)
		return (vec_new(0.3, 0.3));
	else if (type == Entity_Medikit)
		return (vec_new(0.75, 0.75));
	else if (type == Entity_Money)
		return (vec_new(0.75, 0.75));
	else if (type >= Entity_Sprite1 && type <= Entity_Sprite4)
		return (vec_new(1, 1));
	else if (type == Entity_Enemy1)
		return (vec_new(0.75, 0.75));
	else if (type == Entity_Shell)
		return (vec_new(0.75, 0.75));
	else if (type == Entity_Bullet)
		return (vec_new(0.75, 0.75));
	else if (type == Entity_Shotgun)
		return (vec_new(0.75, 0.75));
	else if (type == Entity_Enemy2)
		return (vec_new(1.0, 1.0));
	return (vec_new(0, 0));
}

t_vector2		entity_get_scale(int type)
{
	if (type == Entity_Medikit)
		return (vec_new(0.30, 0.2));
	if (type == Entity_Money)
		return (vec_new(0.3, 0.2));
	else if (type == Entity_Sprite1)
		return (vec_new(0.42, 1));
	else if (type == Entity_Sprite4)
		return (vec_new(0.32, 1.5));
	else if (type == Entity_Sprite2)
		return (vec_new(0.32, 0.8));
	else if (type == Entity_Sprite3)
		return (vec_new(0.24, 0.6));
	else if (type == Entity_Enemy1)
		return (vec_new(0.5, 0.65));
	else if (type == Entity_Enemy2)
		return (vec_new(1.32, 1.4));
	else if (type == Entity_Shell)
		return (vec_new(0.15, 0.1));
	else if (type == Entity_Bullet)
		return (vec_new(0.15, 0.2));
	else if (type == Entity_Shotgun)
		return (vec_new(0.6, 0.2));
	return (vec_new(1.0, 1.0));
}

double			entity_get_yoffset(int type)
{
	if (type == Entity_Sprite2)
		return (0.1);
	else if (type == Entity_Medikit || type == Entity_Money ||
			type == Entity_Bullet)
		return (0.4);
	else if (type == Entity_Sprite4)
		return (-0.225);
	else if (type == Entity_Sprite3)
		return (0.17);
	else if (type == Entity_Enemy1)
		return (0.2);
	else if (type == Entity_Enemy2)
		return (-0.22);
	else if (type == Entity_Shell || type == Entity_Shotgun)
		return (0.45);
	return (0.0);
}

int				entity_get_texid(t_entity *e)
{
	if (e->type == Entity_Medikit)
		return (Id_Medikit);
	else if (e->type == Entity_Sprite1)
		return (Id_Sprite1);
	else if (e->type == Entity_Sprite2)
		return (Id_Sprite2);
	else if (e->type == Entity_Sprite3)
		return (Id_Sprite3);
	else if (e->type == Entity_Sprite4)
		return (Id_Sprite4);
	else if (e->type == Entity_Money)
		return (Id_Money);
	else if (e->type == Entity_Bullet)
		return (Id_Weapon1A);
	else if (e->type == Entity_Shell)
		return (Id_Weapon2A);
	else if (e->type == Entity_Shotgun)
		return (Id_Weapon2I);
	return (Id_Null);
}

t_bool			entity_is_pickable(int type)
{
	if (type == Entity_Medikit)
		return (TRUE);
	else if (type == Entity_Money)
		return (TRUE);
	else if (type == Entity_Bullet)
		return (TRUE);
	else if (type == Entity_Shell)
		return (TRUE);
	else if (type == Entity_Shotgun)
		return (TRUE);
	return (FALSE);
}
