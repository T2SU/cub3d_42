/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 20:47:35 by smun              #+#    #+#             */
/*   Updated: 2021/01/14 14:33:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool		input_on_mousebtnup(int btn, int x, int y, t_game *g)
{
	if (btn < 0 || btn >= MouseBtn_Num)
		return (FALSE);
	if (x < 0 || x >= g->screensize.width)
		return (FALSE);
	if (y < 0 || y >= g->screensize.height)
		return (FALSE);
	g->input.mouse.x = x;
	g->input.mouse.y = y;
	g->input.mousebtn[btn] = FALSE;
	return (TRUE);
}

t_bool		input_on_mousebtndown(int btn, int x, int y, t_game *g)
{
	if (btn < 0 || btn >= MouseBtn_Num)
		return (FALSE);
	if (x < 0 || x >= g->screensize.width)
		return (FALSE);
	if (y < 0 || y >= g->screensize.height)
		return (FALSE);
	g->input.mouse.x = x;
	g->input.mouse.y = y;
	g->input.mousebtn[btn] = TRUE;
	return (TRUE);
}

t_bool		input_on_mousemove(int x, int y, t_game *g)
{
	if (x < 0 || x >= g->screensize.width)
		return (FALSE);
	if (y < 0 || y >= g->screensize.height)
		return (FALSE);
	g->input.mouse.x = x;
	g->input.mouse.y = y;
	return (TRUE);
}
