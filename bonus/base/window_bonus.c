/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:31:55 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 02:41:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <mlx.h>

static void	change_mouse_hide_mode(t_game *g, t_bool mode)
{
	g->hidemouse = mode;
	mlx_mouse_move(g->win_ptr,
		g->screensize.width / 2, g->screensize.height / 2);
	if (mode)
	{
		mlx_mouse_hide();
	}
	else
	{
		mlx_mouse_show();
	}
}

int			window_on_expose(t_game *g)
{
	if (!g->hidemouse)
		change_mouse_hide_mode(g, TRUE);
	else
		mlx_mouse_hide();
	return (0);
}

void		window_on_esc(t_game *g)
{
	if (g->hidemouse)
		change_mouse_hide_mode(g, FALSE);
}

int			window_on_close(t_game *g)
{
	return (app_exit(g));
}

int			window_mouse(t_game *g)
{
	t_size	sz;

	sz = g->screensize;
	if (g->input.mouse.x > 0 && g->input.mouse.x < sz.width &&
		g->input.mouse.y > 0 && g->input.mouse.y < sz.height &&
		g->input.mousebtn[MouseBtn_Left])
		window_on_expose(g);
	if (g->hidemouse)
		mlx_mouse_move(g->win_ptr, sz.width / 2, sz.height / 2);
	return (0);
}
