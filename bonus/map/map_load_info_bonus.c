/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_info_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:36:50 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 04:45:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include <mlx.h>

static t_bool	load_textures2(t_game *g, int *r, int *i, char *l)
{
	return ((r[(*i)++] = elem_read_str(g, l, "DR1", &g->map.tex[Id_Door1])) &&
		(r[(*i)++] = elem_read_str(g, l, "DR2", &g->map.tex[Id_Door2])) &&
		(r[(*i)++] = elem_read_str(g, l, "WIN", &g->map.tex[Id_GameWin])) &&
		(r[(*i)++] = elem_read_str(g, l, "M1A0", &g->map.tex[Id_Enemy1Std])) &&
		(r[(*i)++] = elem_read_str(g, l, "M1A1", &g->map.tex[Id_Enemy1Mov])) &&
		(r[(*i)++] = elem_read_str(g, l, "M1A2", &g->map.tex[Id_Enemy1Atk])) &&
		(r[(*i)++] = elem_read_str(g, l, "M1A3", &g->map.tex[Id_Enemy1Hit])) &&
		(r[(*i)++] = elem_read_str(g, l, "M1A4", &g->map.tex[Id_Enemy1Die])) &&
		(r[(*i)++] = elem_read_str(g, l, "M2A0", &g->map.tex[Id_Enemy2Std])) &&
		(r[(*i)++] = elem_read_str(g, l, "M2A1", &g->map.tex[Id_Enemy2Mov])) &&
		(r[(*i)++] = elem_read_str(g, l, "M2A2", &g->map.tex[Id_Enemy2Atk])) &&
		(r[(*i)++] = elem_read_str(g, l, "M2A3", &g->map.tex[Id_Enemy2Hit])) &&
		(r[(*i)++] = elem_read_str(g, l, "M2A4", &g->map.tex[Id_Enemy2Die])) &&
		(r[(*i)++] = elem_read_str(g, l, "W0", &g->map.tex[Id_Weapon0])) &&
		(r[(*i)++] = elem_read_str(g, l, "W1", &g->map.tex[Id_Weapon1])) &&
		(r[(*i)++] = elem_read_str(g, l, "W2", &g->map.tex[Id_Weapon2])) &&
		(r[(*i)++] = elem_read_str(g, l, "AW1", &g->map.tex[Id_Weapon1A])) &&
		(r[(*i)++] = elem_read_str(g, l, "AW2", &g->map.tex[Id_Weapon2A])) &&
		(r[(*i)++] = elem_read_str(g, l, "IW2", &g->map.tex[Id_Weapon2I])));
}

static t_bool	load_textures(t_game *g, int *r, int *i, char *l)
{
	return ((r[(*i)++] = elem_read_str(g, l, "FLR", &g->map.tex[Id_Floor])) &&
		(r[(*i)++] = elem_read_str(g, l, "SKY", &g->map.tex[Id_Skybox])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL1", &g->map.tex[Id_Wall1])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL2", &g->map.tex[Id_Wall2])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL3", &g->map.tex[Id_Wall3])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL4", &g->map.tex[Id_Wall4])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL5", &g->map.tex[Id_Wall5])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL6", &g->map.tex[Id_Wall6])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL7", &g->map.tex[Id_Wall7])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL8", &g->map.tex[Id_Wall8])) &&
		(r[(*i)++] = elem_read_str(g, l, "WL9", &g->map.tex[Id_Wall9])) &&
		(r[(*i)++] = elem_read_str(g, l, "SPRIT1", &g->map.tex[Id_Sprite1])) &&
		(r[(*i)++] = elem_read_str(g, l, "SPRIT2", &g->map.tex[Id_Sprite2])) &&
		(r[(*i)++] = elem_read_str(g, l, "SPRIT3", &g->map.tex[Id_Sprite3])) &&
		(r[(*i)++] = elem_read_str(g, l, "SPRIT4", &g->map.tex[Id_Sprite4])) &&
		(r[(*i)++] = elem_read_str(g, l, "MONEY", &g->map.tex[Id_Money])) &&
		(r[(*i)++] = elem_read_str(g, l, "ITEM1", &g->map.tex[Id_Medikit])) &&
		(r[(*i)++] = elem_read_str(g, l, "SCORE", &g->map.tex[Id_HudScore])) &&
		(r[(*i)++] = elem_read_str(g, l, "DIGIT", &g->map.tex[Id_Digit])) &&
		(r[(*i)++] = elem_read_str(g, l, "HP", &g->map.tex[Id_HudHp])) &&
		(r[(*i)++] = elem_read_str(g, l, "CRH", &g->map.tex[Id_Crosshair])) &&
		(r[(*i)++] = elem_read_str(g, l, "LOSE", &g->map.tex[Id_GameOver])) &&
		(r[(*i)++] = elem_read_str(g, l, "BAR", &g->map.tex[Id_HudHPBar])) &&
		(r[(*i)++] = elem_read_str(g, l, "GAU", &g->map.tex[Id_HudHPGauge])) &&
		load_textures2(g, r, i, l));
}

static t_bool	map_load_info_line(t_game *g, char *line)
{
	int			res[MAX_RESOURCE];
	int			i;

	if (util_is_empty_line(line))
		return (TRUE);
	i = 0;
	if (!(res[i++] = elem_read_size(g, line, "R", &g->screensize)) ||
		!load_textures(g, res, &i, line))
		return (FALSE);
	g->map.fullloadmask = (1ULL << i) - 1;
	while (i-- > 0)
		if (res[i] == 1)
		{
			if (g->map.loadmask & (1ULL << i))
				return (error_raise(g, Error_DuplicatedMapInfo, line));
			g->map.loadmask |= (1ULL << i);
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
