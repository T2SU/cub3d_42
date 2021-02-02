/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 03:55:54 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:42:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

static t_bool	is_boss_alive(t_game *g)
{
	t_list		*lst;
	t_entity	*e;

	lst = g->map.ent;
	while (lst)
	{
		e = (t_entity*)lst->content;
		if (e->type == Entity_Enemy2 && e->hp > 0)
			return (TRUE);
		lst = lst->next;
	}
	return (FALSE);
}

void			exit_interact(t_game *g, t_entity *p)
{
	if (!is_boss_alive(g))
	{
		sound_play(g, Sound_Switch, p->pos, FALSE);
		player_win(g);
	}
	else
	{
		ft_strlcpy(g->msg,
					"[EXIT] The f**king boss is still alive. Kill him first.",
					MSG_BUF_SIZE);
		g->msgdur = 30;
	}
}
