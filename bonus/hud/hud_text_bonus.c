/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_text_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 23:57:07 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 00:35:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <mlx.h>

void		hud_draw_text(t_game *g)
{
	t_point	pt;

	if (!g->msgdur || !g->msg[0])
		return ;
	g->msgdur--;
	pt = point_new(30, 30);
	mlx_string_put(g->mlx_ptr, g->win_ptr, pt.x, pt.y, Color_Silver, g->msg);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, g->win_ptr);
}
