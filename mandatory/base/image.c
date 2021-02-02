/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:01:22 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 20:25:27 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>

/*
**  Create a new blank image struct instance.
*/

t_image			*image_new(t_game *g, t_size size)
{
	t_image		*i;

	if (!(i = malloc(sizeof(t_image))))
	{
		error_raise(g, Error_System, "failed to image_new");
		return (NULL);
	}
	i->size = size;
	if (!(i->img_ptr = mlx_new_image(g->mlx_ptr, size.width, size.height)))
	{
		error_raise(g, Error_NewImage, NULL);
		free(i);
		return (NULL);
	}
	if (!(i->data_addr = mlx_get_data_addr(i->img_ptr,
			&(i->color_depth), &(i->size_line), &(i->endian))))
	{
		error_raise(g, Error_GetPtrFailed, NULL);
		mlx_destroy_image(g->mlx_ptr, i->img_ptr);
		free(i);
		return (NULL);
	}
	i->bytes_per_pixel = i->color_depth / 8;
	return (i);
}

/*
**  Load an image using the given function.
*/

static t_image	*load_r(t_game *g, char *fn, void *l(void*, char*, int*, int*))
{
	t_image		*i;

	if (!(i = malloc(sizeof(t_image))))
	{
		error_raise(g, Error_System, "failed to load_r");
		return (NULL);
	}
	if (!(i->img_ptr = l(g->mlx_ptr, fn, &i->size.width, &i->size.height)))
	{
		error_raise(g, Error_LoadImage, fn);
		free(i);
		return (NULL);
	}
	if (!(i->data_addr = mlx_get_data_addr(i->img_ptr,
			&(i->color_depth), &(i->size_line), &(i->endian))))
	{
		error_raise(g, Error_GetPtrFailed, fn);
		image_unload(g, i);
		return (NULL);
	}
	error_raise(g, Error_Success, NULL);
	i->bytes_per_pixel = i->color_depth / 8;
	return (i);
}

/*
**  Load an image. try it first by png and if failed, try again by xpm.
**  Case of both failed, return NULL ptr.
*/

t_image			*image_load(t_game *g, t_cchar *filename)
{
	t_image		*i;

	if ((i = load_r(g, (char*)filename, &mlx_png_file_to_image)))
		return (i);
	if ((i = load_r(g, (char*)filename, &mlx_xpm_file_to_image)))
		return (i);
	return (NULL);
}

void			image_unload(t_game *g, t_image *i)
{
	mlx_destroy_image(g->mlx_ptr, i->img_ptr);
	free(i);
}
