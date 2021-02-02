/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_item_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:02:10 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 05:25:10 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

static t_bool	check_in_rect(t_entity *e, t_entity *p)
{
	t_rect		rc_fac;
	t_rect		rc;

	rc_fac.left = e->pos.x;
	rc_fac.top = e->pos.y;
	rc_fac.width = e->size.x;
	rc_fac.height = e->size.y;
	rc = rect_from_size(p->pos, vec_mult_scalar(p->size, 1.5));
	return (rect_overlaps(rc_fac, rc));
}

static void		pickup_item_msg(t_game *g, int type)
{
	if (type == Entity_Bullet)
		ft_strlcpy(g->msg, "You've got some bullets.", MSG_BUF_SIZE);
	else if (type == Entity_Shell)
		ft_strlcpy(g->msg, "You've got some shotgun shells.", MSG_BUF_SIZE);
	else if (type == Entity_Medikit)
		ft_strlcpy(g->msg, "A medikit restores your health.", MSG_BUF_SIZE);
	else if (type == Entity_Money)
		ft_strlcpy(g->msg, "Picked up some money.", MSG_BUF_SIZE);
	else if (type == Entity_Shotgun)
		ft_strlcpy(g->msg, "You've got an AMAZING SHOTGUN. ", MSG_BUF_SIZE);
	else
		return ;
	g->msgdur = 32;
}

static int		pickup_weapon(t_game *g, int type, t_entity *p)
{
	if (type == Entity_Shotgun)
	{
		g->inventory |= (1 << Weapon_Shotgun);
		g->bullets[Ammo_Shell] += 8;
		weapon_player_switch(g, p, Weapon_Shotgun);
	}
	return (Sound_WeaponPickUp);
}

static t_bool	pickup_item(t_game *g, t_entity *e, t_entity *p)
{
	int			colormapclr;
	int			sound;

	colormapclr = Color_LightGreen;
	sound = Sound_ItemPickUp;
	if (e->type == Entity_Medikit && p->hp < p->maxhp)
		p->hp = ft_min(p->hp + 30, p->maxhp);
	else if (e->type == Entity_Medikit)
		return (FALSE);
	if (e->type == Entity_Money)
	{
		g->score += 125;
		colormapclr = Color_LightGray;
	}
	if (e->type == Entity_Bullet)
		g->bullets[Ammo_Bullet] += 10;
	if (e->type == Entity_Shell)
		g->bullets[Ammo_Shell] += 4;
	if (e->type == Entity_Shotgun)
		sound = pickup_weapon(g, e->type, p);
	sound_play(g, sound, p->pos, FALSE);
	screen_setcolormap(g, colormapclr, 3);
	pickup_item_msg(g, e->type);
	return (TRUE);
}

void			player_try_pickup_item(t_game *g, t_entity *p)
{
	t_point		pt;
	t_point		ept;
	t_entity	*e;
	t_list		*lst;
	t_list		*del;

	del = NULL;
	pt = point_from_vector(p->pos);
	lst = g->map.ent;
	while (!del && lst)
	{
		e = ((t_entity*)lst->content);
		ept = point_from_vector(e->pos);
		if (entity_is_pickable(e->type) &&
			pt.x == ept.x && pt.y == ept.y && check_in_rect(e, p))
		{
			if (pickup_item(g, e, p) && (del = lst))
				map_set(&g->map, pt.x, pt.y, '0');
		}
		lst = lst->next;
	}
	util_lstdel_find(g, del);
}
