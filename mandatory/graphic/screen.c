/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 19:46:41 by smun              #+#    #+#             */
/*   Updated: 2021/01/17 20:52:36 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>

t_bool			screen_init(t_game *g)
{
	if (!(g->screen = image_new(g, g->screensize)))
		return (FALSE);
	return (TRUE);
}

void			screen_uninit(t_game *g)
{
	if (g->screen)
	{
		mlx_destroy_image(g->mlx_ptr, g->screen->img_ptr);
		free(g->screen);
	}
}

t_bool			screen_draw(t_game *g)
{
	t_image		*screen;

	screen = g->screen;
	if (!project_3d(g))
		return (FALSE);
	if (!g->win_ptr)
		return (bmp_save(g, g->screen, "screenshot.bmp"));
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, screen->img_ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, g->win_ptr);
	return (TRUE);
}
