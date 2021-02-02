/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texset_load_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:34:08 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:39:26 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include <libft.h>

static t_bool	load(t_game *g, t_texset *tex, char *p, char *pp)
{
	int			i;

	if (!((tex->imgs = ft_calloc(tex->imgcnt, sizeof(t_image*)))))
		return (error_raise(g, Error_System, "texset load failed"));
	i = 0;
	while (i < tex->imgcnt)
	{
		*pp = 'A' + i;
		if (!(tex->imgs[i] = image_load(g, p)))
			return (FALSE);
		if (tex->imgs[i]->bytes_per_pixel != 4)
			return (error_raise(g, Error_InvalidBpp, NULL));
		i++;
	}
	return (TRUE);
}

static t_texset	*cleanup(t_game *g, t_texset *tex, char *p, int err)
{
	int			i;

	if (tex->imgs)
	{
		i = 0;
		while (i < tex->imgcnt)
		{
			if (tex->imgs[i])
				image_unload(g, tex->imgs[i]);
			i++;
		}
		free(tex->imgs);
	}
	if (tex)
		free(tex);
	if (err)
		error_raise(g, err, "texset_new failed");
	if (p)
		free(p);
	return (NULL);
}

t_texset		*texset_empty(t_game *g)
{
	t_texset	*tex;

	if ((tex = malloc(sizeof(t_texset))))
	{
		tex->imgcnt = 1;
		if (!((tex->imgs = ft_calloc(tex->imgcnt, sizeof(t_image*)))))
			return (cleanup(g, tex, NULL, Error_System));
		if (!(tex->imgs[0] = image_new(g, size_new(16, 16))))
			return (cleanup(g, tex, NULL, 0));
	}
	return (tex);
}

t_texset		*texset_new(t_game *g, t_cchar *path)
{
	t_texset	*tex;
	char		*p;
	char		*pp;

	if (!(tex = ft_calloc(1, sizeof(t_texset))))
		return (error_raise(g, Error_System, NULL) ? NULL : NULL);
	if (!(p = ft_strdup(path)))
		return (cleanup(g, tex, p, Error_System));
	pp = ft_strchr(p, '%');
	tex->imgcnt = 0;
	while (tex->imgcnt <= 'Z' - 'A')
	{
		*pp = 'A' + tex->imgcnt;
		if (!util_file_exists(p))
			break ;
		tex->imgcnt++;
	}
	if (!load(g, tex, p, pp))
		return (cleanup(g, tex, p, 0));
	free(p);
	return (tex);
}

void			texset_delete(t_game *g, t_texset *tex)
{
	cleanup(g, tex, NULL, 0);
}
