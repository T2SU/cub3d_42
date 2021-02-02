/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:36:03 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 04:23:49 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool		block_is_sprite(int c)
{
	return (c == 'B' || c == 'C' || c == 'L' || c == 'P');
}

t_bool		block_is_life(int c)
{
	return (c == 's' || c == 'w' || c == 'e' || c == 'n' || c == 'X');
}

t_bool		block_is_exit(int c)
{
	return (c == '9');
}
