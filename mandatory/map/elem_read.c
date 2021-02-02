/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:29:03 by smun              #+#    #+#             */
/*   Updated: 2021/01/20 11:42:43 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>

static t_bool	cleanup(t_game *g, char *str, int err, t_cchar *desc)
{
	if (str)
		free(str);
	if (err)
		return (error_raise(g, err, desc));
	return (TRUE);
}

static t_bool	cleanups(t_game *g, char **arr, int err, t_cchar *desc)
{
	int			i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
	if (err)
		return (error_raise(g, err, desc));
	return (TRUE);
}

int				elem_read_str(t_game *g, char *line, t_cchar *id, char **dat)
{
	size_t		idlen;

	idlen = ft_strlen(id);
	if (0 == ft_strncmp(line, id, idlen))
	{
		if (line[0] == 'S' && id[0] == 'S' && idlen == 1 && line[1] == 'O')
			return (-1);
		if (!(*dat = ft_strtrim(&line[idlen], " ")))
			return (error_raise(g, Error_StrTrimFailed, line));
		if ((*dat)[0] == line[idlen])
			return (error_raise(g, Error_UnexpectedIdentifier, line));
		return (TRUE);
	}
	return (-1);
}

/*
**     [id]  RR, GG, BB
** -->
**     0xRRGGBB
*/

int				elem_read_color(t_game *g, char *line, t_cchar *id, int *data)
{
	size_t		idlen;
	char		**colors;
	int			color;
	int			i;

	if (ft_strncmp(line, id, (idlen = ft_strlen(id))))
		return (-1);
	if (line[idlen] != ' ')
		return (error_raise(g, Error_UnexpectedIdentifier, line));
	if (!(colors = ft_split(&line[idlen], ',')))
		return (error_raise(g, Error_StrSplitFailed, line));
	if (util_chrcnt(&line[idlen], ',') != 2 ||
		!colors[0] || !colors[1] || !colors[2] || colors[3])
		return (cleanups(g, colors, Error_UnparsableColor, line));
	i = 0;
	while (i < 3)
	{
		if (!util_is_digits(colors[i]))
			return (cleanups(g, colors, Error_UnparsableColor, line));
		color = util_atoi(colors[i]);
		if (color < 0 || color > 255)
			return (cleanups(g, colors, Error_InvalidColor, line));
		*data |= (color << ((2 - (i++)) * 8));
	}
	return (cleanups(g, colors, Error_Success, NULL));
}

int				elem_read_size(t_game *g, char *l, t_cchar *id, t_size *sz)
{
	size_t		idlen;
	char		*trimmed;
	char		**datas;

	idlen = ft_strlen(id);
	if (ft_strncmp(l, id, idlen))
		return (-1);
	if (!(trimmed = ft_strtrim(&l[idlen], " ")))
		return (error_raise(g, Error_StrTrimFailed, l));
	if (trimmed[0] == l[idlen])
		return (cleanup(g, trimmed, Error_UnexpectedIdentifier, l));
	if (!(datas = ft_split(trimmed, ' ')))
		return (cleanup(g, trimmed, Error_StrSplitFailed, l));
	free(trimmed);
	if (!datas[0] || !datas[1] || datas[2])
		return (cleanups(g, datas, Error_UnparsableResolution, l));
	if (!util_is_digits(datas[0]) || !util_is_digits(datas[1]))
		return (cleanups(g, datas, Error_UnparsableResolution, l));
	if ((sz->width = util_atoi(datas[0])) <= 0)
		return (cleanups(g, datas, Error_InvalidScreenSize, l));
	if ((sz->height = util_atoi(datas[1])) <= 0)
		return (cleanups(g, datas, Error_InvalidScreenSize, l));
	return (cleanups(g, datas, Error_Success, NULL));
}
