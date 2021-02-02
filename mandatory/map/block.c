/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:55:08 by smun              #+#    #+#             */
/*   Updated: 2021/01/18 14:22:15 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool		block_is_wall(int c)
{
	return (c == '1');
}

t_bool		block_is_void(int c)
{
	return (c == ' ');
}

t_bool		block_is_walkable(int c)
{
	return (c == '0' || block_is_item(c));
}

t_bool		block_is_item(int c)
{
	return (c == '2');
}
