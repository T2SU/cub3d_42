/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_game_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:09:21 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 19:24:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			player_game_restart(t_game *g)
{
	if (!map_load(g, g->mapfile, TRUE))
		return ;
	app_init_variables(g);
	g->gameover = GameOver_None;
	g->colormapdur = 0;
	texset_resetframe(g, hud_to_resid(g, Hud_Weapon));
	g->cheat = 0;
	g->attention = NULL;
	g->attentiondur = 0;
}

void			player_game_over(t_game *g)
{
	g->gameover = GameOver_Dead;
	g->gameovertick = g->tick.loopcnt + 10;
	screen_setcolormap(g, Color_DeadRed, ~0);
}

void			player_win(t_game *g)
{
	g->gameover = GameOver_Win;
	g->gameovertick = g->tick.loopcnt + 10;
	sound_stop(g, Sound_BGM2);
	sound_play(g, Sound_BGM3, g->player.pos, FALSE);
}
