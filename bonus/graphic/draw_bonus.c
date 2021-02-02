/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:20:08 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:42:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			draw_pixel(t_game *g, int x, int y, int color)
{
	char		*ptr;
	int			pos;

	ptr = g->screen->data_addr;
	pos = y * g->screen->size_line + (x << 2);
	*(int*)(&ptr[pos]) = color;
}
