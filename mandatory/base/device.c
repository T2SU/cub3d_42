/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:48:41 by smun              #+#    #+#             */
/*   Updated: 2021/01/20 11:42:43 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>

static int		on_window_close(t_game *g)
{
	return (app_exit(g));
}

static void		register_input_hook(t_game *g)
{
	mlx_do_key_autorepeatoff(g->mlx_ptr);
	mlx_hook(g->win_ptr, HookEvent_KeyUp, 0, &input_on_keyup, g);
	mlx_hook(g->win_ptr, HookEvent_KeyDown, 0, &input_on_keydown, g);
	mlx_hook(g->win_ptr, HookEvent_MouseBtnUp, 0, &input_on_mousebtnup, g);
	mlx_hook(g->win_ptr, HookEvent_MouseBtnDown, 0, &input_on_mousebtndown, g);
	mlx_hook(g->win_ptr, HookEvent_MouseMove, 0, &input_on_mousemove, g);
}

t_bool			device_mlx_init(t_game *g)
{
	if (!(g->z = malloc(sizeof(double) * g->screensize.width)))
		return (error_raise(g, Error_System, "failed alloc zbuffer"));
	if (!(g->mlx_ptr = mlx_init()))
		return (error_raise(g, Error_MLX_InitFailed, NULL));
	return (TRUE);
}

t_bool			device_window_init(t_game *g, t_bool has_window)
{
	t_size		z;

	z = g->screensize;
	if (!has_window)
		return (TRUE);
	if (!(g->win_ptr = mlx_new_window(g->mlx_ptr, z.width, z.height, "cub3D")))
		return (error_raise(g, Error_MLX_CreateWindowFailed, NULL));
	register_input_hook(g);
	mlx_hook(g->win_ptr, HookEvent_CloseWindow, 0, &on_window_close, g);
	return (TRUE);
}
