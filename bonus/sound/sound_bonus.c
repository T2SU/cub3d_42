/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:39:11 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:49:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include <libft.h>

void		sound_play(t_game *g, int sound, t_vector2 pos, t_bool loop)
{
	char	buffer[260];
	int		vol;
	double	dist;
	char	*volstr;

	if (sound < 0 || sound >= Sound_Num || !g->resource.sounds[sound])
		return ;
	dist = util_distance(g->player.pos, pos);
	ft_strlcpy(buffer, "./play ", sizeof(buffer));
	if (loop)
		ft_strlcat(buffer, "-l ", sizeof(buffer));
	vol = loop ? 50 : 100;
	if (dist > 4)
		vol = (int)(vol - (dist - 4));
	if (vol < 0)
		return ;
	ft_strlcat(buffer, " -v ", 260);
	if (!(volstr = ft_itoa(vol)))
		return ;
	ft_strlcat(buffer, volstr, 260);
	ft_strlcat(buffer, " ", 260);
	ft_strlcat(buffer, g->resource.sounds[sound], sizeof(buffer));
	ft_strlcat(buffer, " &", sizeof(buffer));
	system(buffer);
	free(volstr);
}

void		sound_stop(t_game *g, int sound)
{
	char	buffer[260];

	if (sound < 0 || sound >= Sound_Num || !g->resource.sounds[sound])
		return ;
	ft_strlcpy(buffer, "./stop ", sizeof(buffer));
	ft_strlcat(buffer, g->resource.sounds[sound], sizeof(buffer));
	ft_strlcat(buffer, " &", sizeof(buffer));
	system(buffer);
}
