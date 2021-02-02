/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:31:18 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:48:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mlx.h>

static t_bool	cleanup(int fd, char *buf)
{
	if (fd >= 0)
		close(fd);
	if (buf)
		free(buf);
	return (FALSE);
}

static t_bool	putdata_fd(int fd, void *p, ssize_t len)
{
	t_uint64	val;

	if (len < 0)
	{
		val = (t_uint64)p;
		len = -len;
		p = &val;
	}
	if (write(fd, p, len) < 0)
		return (FALSE);
	return (TRUE);
}

/*
** https://en.wikipedia.org/wiki/BMP_file_format
** <<HEADER>>
** 42 4D
** 8C C2 07 00
** 00 00
** 00 00
** 36 00 00 00
** http://telnet.or.kr/directx/htm/bitmapinfoheaderstructure.htm
** <<DIB header/Windows>>
** 28 00 00 00
** F4 01 00 00
** 53 01 00 00
** 01 00
** 18 00
** 00 00 00 00
** 56 C2 07 00
** C3 0E 00 00
** C3 0E 00 00
** 00 00 00 00
** 00 00 00 00
*/

static t_bool	write_header(t_game *g, int fd, size_t buflen, t_image *img)
{
	if (!putdata_fd(fd, "BM", 2) ||
		!putdata_fd(fd, (void*)(buflen + 54), -4) ||
		!putdata_fd(fd, (void*)0, -2) ||
		!putdata_fd(fd, (void*)0, -2) ||
		!putdata_fd(fd, (void*)54, -4) ||
		!putdata_fd(fd, (void*)40, -4) ||
		!putdata_fd(fd, &img->size.width, 4) ||
		!putdata_fd(fd, &img->size.height, 4) ||
		!putdata_fd(fd, (void*)1, -2) ||
		!putdata_fd(fd, (void*)24, -2) ||
		!putdata_fd(fd, (void*)0, -4) ||
		!putdata_fd(fd, &buflen, 4) ||
		!putdata_fd(fd, (void*)2835, -4) ||
		!putdata_fd(fd, (void*)2835, -4) ||
		!putdata_fd(fd, (void*)0, -4) ||
		!putdata_fd(fd, (void*)0, -4))
		return (error_raise(g, Error_System, "bmp header write failed"));
	return (TRUE);
}

/*
**  ref: https://en.wikipedia.org/wiki/BMP_file_format
**
** bpl = Bytes Per Line
*/

static t_bool	make_buffer(t_game *g, t_image *img, size_t *buflen, char **buf)
{
	size_t		bpl;
	int			y;
	int			x;
	int			clr;
	size_t		ptrpos;

	bpl = (24 * img->size.width + 31) / 32 * 4;
	*buflen = bpl * img->size.height;
	if (!(*buf = ft_calloc(1, *buflen)))
		return (error_raise(g, Error_System, "bmp make buffer failed"));
	y = 0;
	while (++y <= img->size.height)
	{
		x = -1;
		while (++x < img->size.width)
		{
			ptrpos = (y - 1) * img->size_line;
			ptrpos += x * img->bytes_per_pixel;
			ft_memcpy(&clr, &img->data_addr[ptrpos], img->bytes_per_pixel);
			clr = ((int)mlx_get_color_value(g->mlx_ptr, clr)) & 0xffffff;
			ft_memcpy(&(*buf)[(img->size.height - y) * bpl + 3 * x], &clr, 3);
		}
	}
	return (TRUE);
}

/*
**  ref: https://stackoverflow.com/questions/13745093
** technical-recipes.com/2011/creating-bitmap-files-from-raw-pixel-data-in-c/
** https://stackoverflow.com/questions/2245193
*/

t_bool			bmp_save(t_game *g, t_image *img, t_cchar *filename)
{
	char		*buf;
	size_t		buflen;
	int			fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (error_raise(g, Error_System, "bmp save 'open' failed"));
	if (!make_buffer(g, img, &buflen, &buf))
		return (cleanup(fd, buf));
	if (!write_header(g, fd, buflen, img))
		return (cleanup(fd, buf));
	if (write(fd, buf, buflen) < 0)
		return (cleanup(fd, buf));
	cleanup(fd, buf);
	return (TRUE);
}
