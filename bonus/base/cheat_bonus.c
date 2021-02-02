/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheat_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 22:36:24 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:38:44 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

static void	toggle_cheat(t_game *g, int c, t_cchar *txt)
{
	ft_strlcpy(g->msg, "[Cheat] ", MSG_BUF_SIZE);
	ft_strlcat(g->msg, txt, MSG_BUF_SIZE);
	if (g->cheat & c)
	{
		g->cheat &= ~c;
		ft_strlcat(g->msg, " Disabled.", MSG_BUF_SIZE);
	}
	else
	{
		g->cheat |= c;
		ft_strlcat(g->msg, " Enabled.", MSG_BUF_SIZE);
	}
	g->cheatdelay = 5;
	g->msgdur = 32;
}

void		cheat_update(t_game *g)
{
	if (g->cheatdelay)
	{
		g->cheatdelay--;
		return ;
	}
	if (g->input.key[Key_F1])
		toggle_cheat(g, Cheat_God, "God Mode");
	else if (g->input.key[Key_F2])
		toggle_cheat(g, Cheat_Ammo, "Infinite Ammo Mode");
	else if (g->input.key[Key_F3])
		toggle_cheat(g, Cheat_Transcendence, "Transcendence Mode");
	else if (g->input.key[Key_F4])
		toggle_cheat(g, Cheat_OneShot, "OneShot Mode");
}
