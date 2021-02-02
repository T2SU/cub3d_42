/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:03:03 by smun              #+#    #+#             */
/*   Updated: 2021/01/18 21:46:24 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

static void	print_error(t_game *g)
{
	t_cchar	*errmsg;

	if (g->error == Error_System)
		perror("Error\ncub3D");
	else if ((errmsg = error_get_msg(g, g->error)))
		printf("Error\ncub3D: %s", errmsg);
	else
		printf("Error\nUnknown Error[%d] ", g->error);
	if (ft_strlen(g->errordesc))
		printf("(%s)", g->errordesc);
	printf("\n");
}

int			app_exit(t_game *g)
{
	if (g->z)
		free(g->z);
	if (g->mlx_ptr)
		resources_unload(g);
	screen_uninit(g);
	if (g->mlx_ptr && g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	map_unload(g);
	if (error_is_raised(g))
		print_error(g);
	exit(g->error ? EXIT_FAILURE : EXIT_SUCCESS);
	return (g->error ? EXIT_FAILURE : EXIT_SUCCESS);
}

void		app_init_variables(t_game *g)
{
	tick_init(g);
	player_init(g);
}

t_bool		app_on_loop(t_game *g)
{
	if (error_is_raised(g) || g->input.key[Key_ESC])
		return (app_exit(g));
	if (tick_update(g))
	{
		player_update(g);
		if (!screen_draw(g))
			return (FALSE);
	}
	return (TRUE);
}
