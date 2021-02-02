/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:20:08 by smun              #+#    #+#             */
/*   Updated: 2021/01/19 00:10:43 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

void			draw_pixel(t_game *g, int x, int y, int color)
{
	char		*ptr;
	int			pos;

	ptr = g->screen->data_addr;
	pos = y * g->screen->size_line;
	pos += x * g->screen->bytes_per_pixel;
	if (g->screen->bytes_per_pixel == sizeof(int))
		*(int*)(&ptr[pos]) = color;
	else
		ft_memcpy(&ptr[pos], &color, g->screen->bytes_per_pixel);
}
