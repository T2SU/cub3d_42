/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:48:29 by smun              #+#    #+#             */
/*   Updated: 2021/01/19 02:04:50 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <mlx.h>

static int	exit_with_error(t_game *g, int err, t_cchar *desc)
{
	error_raise(g, err, desc);
	return (app_exit(g));
}

static int	save_screenshot_and_exit(t_game *g)
{
	screen_draw(g);
	return (app_exit(g));
}

int			main(int argc, char **argv)
{
	t_game	g;
	t_bool	real_game;

	ft_bzero(&g, sizeof(t_game));
	error_init(&g);
	if (argc <= 1)
		return (exit_with_error(&g, Error_ArgumentLacked, NULL));
	real_game = argc < 3;
	if (!real_game && (ft_strncmp(argv[2], "--save", 7) || argc > 3))
		return (exit_with_error(&g, Error_InvalidArgument, argv[2]));
	if (!map_load(&g, argv[1], real_game))
		return (exit_with_error(&g, g.error, g.errordesc));
	if (!device_mlx_init(&g) || !resources_load(&g))
		return (exit_with_error(&g, g.error, g.errordesc));
	if (!device_window_init(&g, real_game) || !screen_init(&g))
		return (exit_with_error(&g, g.error, g.errordesc));
	app_init_variables(&g);
	if (!real_game)
		return (save_screenshot_and_exit(&g));
	mlx_loop_hook(g.mlx_ptr, &app_on_loop, &g);
	mlx_loop(g.mlx_ptr);
	return (0);
}
