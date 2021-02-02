/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:36:50 by smun              #+#    #+#             */
/*   Updated: 2021/01/18 21:11:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <mlx.h>

static t_bool	map_load_info_line(t_game *g, char *line)
{
	int			res[MAX_RESOURCE];
	int			i;

	if (util_is_empty_line(line))
		return (TRUE);
	i = 0;
	if (!(res[i++] = elem_read_size(g, line, "R", &g->screensize)) ||
		!(res[i++] = elem_read_str(g, line, "NO", &g->map.tex[Id_TextureN])) ||
		!(res[i++] = elem_read_str(g, line, "SO", &g->map.tex[Id_TextureS])) ||
		!(res[i++] = elem_read_str(g, line, "EA", &g->map.tex[Id_TextureE])) ||
		!(res[i++] = elem_read_str(g, line, "WE", &g->map.tex[Id_TextureW])) ||
		!(res[i++] = elem_read_str(g, line, "S", &g->map.tex[Id_Sprite])) ||
		!(res[i++] = elem_read_color(g, line, "C", &g->map.color_ceil)) ||
		!(res[i++] = elem_read_color(g, line, "F", &g->map.color_floor)))
		return (FALSE);
	g->map.fullloadmask = (1 << i) - 1;
	while (i-- > 0)
		if (res[i] == 1)
		{
			if (g->map.loadmask & (1 << i))
				return (error_raise(g, Error_DuplicatedMapInfo, line));
			g->map.loadmask |= (1 << i);
			return (TRUE);
		}
	return (error_raise(g, Error_InvalidIdentifier, line));
}

static void		ensure_in_display_size(t_game *g)
{
	t_size		sz;

	mlx_get_screen_size(g->mlx_ptr,
		&sz.width, &sz.height);
	g->screensize.width = ft_min(sz.width, g->screensize.width);
	g->screensize.height = ft_min(sz.height, g->screensize.height);
}

t_bool			map_load_info(t_game *g, int fd, t_bool real_game)
{
	int			status;
	char		*line;
	char		*trimmed;

	while ((!g->map.fullloadmask || g->map.loadmask != g->map.fullloadmask) &&
			(status = get_next_line(fd, &line)) >= 0)
	{
		util_unify_spaces(&line);
		trimmed = ft_strtrim(line, " ");
		free(line);
		if (trimmed == NULL)
			return (error_raise(g, Error_System, "ft_strtrim failed."));
		map_load_info_line(g, trimmed);
		free(trimmed);
		if (error_is_raised(g) || status == 0)
			break ;
	}
	if (status == -1)
		return (error_raise(g, Error_System, "gnl failed."));
	if (!error_is_raised(g) && g->map.loadmask != g->map.fullloadmask)
		return (error_raise(g, Error_InvalidMapInfo, "missing map elem."));
	if (real_game)
		ensure_in_display_size(g);
	return (!error_is_raised(g));
}
