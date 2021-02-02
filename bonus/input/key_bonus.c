/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:10:08 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 22:46:59 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool		input_on_keyup(int keycode, t_game *g)
{
	if (keycode < 0 || keycode >= Key_Num)
		return (FALSE);
	(g->input.key)[keycode] = FALSE;
	return (TRUE);
}

t_bool		input_on_keydown(int keycode, t_game *g)
{
	if (keycode < 0 || keycode >= Key_Num)
		return (FALSE);
	(g->input.key)[keycode] = TRUE;
	return (TRUE);
}
