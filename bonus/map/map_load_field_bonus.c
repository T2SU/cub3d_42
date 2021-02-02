/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_field_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:10:49 by smun              #+#    #+#             */
/*   Updated: 2021/01/29 21:54:49 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>
#include <stdlib.h>

static t_bool	cleanups(t_game *g, t_list **lst, int err, t_cchar *desc)
{
	ft_lstclear(lst, &free);
	if (err)
		return (error_raise(g, err, desc));
	return (TRUE);
}

static t_bool	convert_field_data(t_game *g, int x, int y, t_cchar *line)
{
	t_map		*m;
	int			c;

	m = &g->map;
	c = (int)ft_strlen(line) > x ? line[x] : ' ';
	if (ft_strchr("SWNE0", c) || block_is_wall(c) || block_is_item(c) ||
		block_is_void(c) || block_is_door(c) || block_get_secret_look(c) ||
		block_is_sprite(c) || block_is_life(c))
	{
		if (block_is_door(c))
			m->doorcnt++;
		if (block_get_secret_look(c))
			m->secretcnt++;
		map_set(m, x, y, c);
		return (TRUE);
	}
	return (error_raise(g, Error_UnknownFieldCharacter, line));
}

static t_bool	parse_field_data(t_game *g, t_map *m, t_list **lst)
{
	int			x;
	int			y;
	t_list		*cur;

	if (!(m->field = ft_calloc(m->size.height * m->size.width, sizeof(int))))
		return (cleanups(g, lst, Error_System, "failed to calloc map field"));
	cur = *lst;
	y = 0;
	while (cur)
	{
		x = 0;
		while (x < m->size.width)
			if (!convert_field_data(g, x++, y, (char*)cur->content))
				return (cleanups(g, lst, g->error, NULL));
		cur = cur->next;
		y++;
	}
	m->size.height = y;
	return (TRUE);
}

t_bool			map_load_field(t_game *g, int fd)
{
	int			status;
	char		*line;
	t_list		*elem;
	t_list		*lst;

	lst = NULL;
	while ((status = get_next_line(fd, &line)) >= 0)
	{
		util_unify_spaces(&line);
		if (!(elem = ft_lstnew(line)))
			return (cleanups(g, &lst, Error_System, line));
		g->map.size.width = ft_max(g->map.size.width, ft_strlen(line));
		g->map.size.height++;
		ft_lstadd_back(&lst, elem);
		if (status == 0)
			break ;
	}
	if (status < 0)
		return (cleanups(g, &lst, Error_System, "gnl failed."));
	if (!parse_field_data(g, &g->map, &lst) || !map_validate(g, &g->map))
		return (FALSE);
	return (cleanups(g, &lst, Error_Success, NULL));
}
