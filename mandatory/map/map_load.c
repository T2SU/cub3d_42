/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:11:10 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 20:18:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static t_bool	check_texture_path(t_game *g)
{
	int			i;

	i = 0;
	while (g->map.tex[++i])
	{
		if (!util_file_exists(g->map.tex[i]))
			return (error_raise(g, Error_System, g->map.tex[i]));
		if (!util_file_extension(g->map.tex[i], ".png") &&
			!util_file_extension(g->map.tex[i], ".xpm"))
			return (error_raise(g, Error_InvalidFileExtension, g->map.tex[i]));
	}
	return (TRUE);
}

t_bool			map_load(t_game *g, t_cchar *file, t_bool real_game)
{
	int			fd;

	map_unload(g);
	if (!util_file_extension(file, ".cub"))
		return (error_raise(g, Error_InvalidFileExtension, file));
	if ((fd = open(file, O_RDONLY)) < 0)
		return (error_raise(g, Error_System, file));
	if (!map_load_info(g, fd, real_game) ||
		!map_load_field(g, fd) ||
		!map_load_entity(g))
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	if (!check_texture_path(g))
		return (FALSE);
	return (TRUE);
}

void			map_unload(t_game *g)
{
	int			i;

	i = 0;
	while (i < MAX_RESOURCE)
	{
		if (g->map.tex[i])
			free(g->map.tex[i]);
		i++;
	}
	ft_lstclear(&g->map.ent, &free);
	if (g->map.field)
		free(g->map.field);
	ft_bzero(&g->map, sizeof(t_map));
}
