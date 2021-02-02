/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:11:10 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 20:23:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

static t_bool	failed(t_game *g, void *ptr, int err, t_cchar *desc)
{
	error_raise(g, err, desc);
	free(ptr);
	return (FALSE);
}

static t_bool	check_texture_path(t_game *g)
{
	int			i;
	char		*b;
	char		*bp;

	i = 0;
	while (g->map.tex[++i])
	{
		if (!ft_strchr(g->map.tex[i], '%'))
			return (error_raise(g, Error_NoTexIdSymbol, g->map.tex[i]));
		if (!(b = ft_strdup(g->map.tex[i])))
			return (error_raise(g, Error_System, NULL));
		bp = ft_strchr(b, '%');
		*bp = 'A';
		if (!util_file_extension(b, ".png") &&
			!util_file_extension(b, ".xpm"))
			return (failed(g, b, Error_InvalidFileExtension, g->map.tex[i]));
		if (!util_file_exists(b))
			return (failed(g, b, Error_System, b));
		free(b);
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
	if (!map_load_facility(g, g->map.doorcnt, g->map.secretcnt))
		return (FALSE);
	if (!check_texture_path(g))
		return (FALSE);
	if (real_game)
		sound_play(g, Sound_BGM1, g->player.pos, TRUE);
	return (TRUE);
}

static void		free_objects(void **ptr, int cnt)
{
	int			i;

	if (ptr)
	{
		i = cnt - 1;
		while (i >= 0 && ptr[i])
			free(ptr[i--]);
		free(ptr);
	}
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
	if (g->map.door)
		free_objects((void**)g->map.door, g->map.doorcnt);
	if (g->map.secret)
		free_objects((void**)g->map.secret, g->map.secretcnt);
	ft_bzero(&g->map, sizeof(t_map));
	i = 0;
	while (i < Sound_Num)
		sound_stop(g, i++);
}
