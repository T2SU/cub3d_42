/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:55:08 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 02:50:18 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool		block_is_wall(int c)
{
	return (c >= '1' && c <= '9');
}

t_bool		block_is_void(int c)
{
	return (c == ' ');
}

t_bool		block_is_item(int c)
{
	return (c == 'M' || c == 'm' || c == 'A' || c == 'a' || c == 'G');
}

t_bool		block_is_door(int c)
{
	return (c == 'D' || c == 'd');
}

int			block_get_secret_look(int c)
{
	if (c == '!')
		return ('1');
	if (c == '@')
		return ('2');
	if (c == '#')
		return ('3');
	if (c == '$')
		return ('4');
	if (c == '%')
		return ('5');
	if (c == '^')
		return ('6');
	if (c == '&')
		return ('7');
	if (c == '*')
		return ('8');
	if (c == '(')
		return ('9');
	return (0);
}
