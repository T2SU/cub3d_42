/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 21:38:20 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 20:13:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

t_bool		util_file_exists(t_cchar *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY | O_SHLOCK)) < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

t_bool		util_file_extension(t_cchar *filename, t_cchar *ext)
{
	size_t	len;
	size_t	extlen;

	len = ft_strlen(filename);
	extlen = ft_strlen(ext);
	if (len < extlen)
		return (FALSE);
	filename += (len - extlen);
	return (ft_strncmp(filename, ext, extlen) == 0);
}
