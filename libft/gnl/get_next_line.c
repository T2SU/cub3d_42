/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:58:09 by smun              #+#    #+#             */
/*   Updated: 2021/01/09 01:02:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static t_reader		*new_reader(void)
{
	t_reader		*ret;

	if ((ret = malloc(sizeof(t_reader))))
	{
		ret->buffer = NULL;
		ret->len = 0;
		ret->eof = FALSE;
	}
	return (ret);
}

/*
** Do append buffer's contents to previously existing string pointer.
**
** == Summary ==
**   1. reader->len > 0
**       This case means there is a something string already.
**       so we should copy it first than appending just read buffer.
**
**         reader->buffer = reader->buffer + buffer
**
**   2. reader->len == 0
**       otherwise, there is no string pointer made before.
**       we can only append just read buffer.
**
**         reader->buffer = buffer
**
** * If it occurs an error in malloc, function will return a NULL pointer.
**   we can use it for handing error in main function.
*/

static t_bool		append_buffer(t_reader *reader, char *buffer, ssize_t len)
{
	char			*ret;

	if ((ret = malloc(len + reader->len)))
	{
		ft_memcpy(&ret[0], reader->buffer, reader->len);
		ft_memcpy(&ret[reader->len], buffer, len);
		reader->len += len;
	}
	if (reader->buffer)
		free(reader->buffer);
	return ((reader->buffer = ret) ? TRUE : FALSE);
}

static ssize_t		ft_indexof(const char *s, int c, size_t len)
{
	ssize_t			i;

	if (s != NULL)
	{
		i = 0;
		while (i < (ssize_t)len)
		{
			if (s[i] == (char)c)
				return (i);
			i++;
		}
	}
	return (-1);
}

/*
** Make a line from the buffered reader.
**
** == Summary ==
**   1. We want a line separator is located in buffer.
**      for this we will use 'ft_indexof' function to find it.
**
**   2. 'ft_indexof' return separator index of first found character.
**      so we can know where is a line separator in string buffer.
**
**   3. If we recognize a line separator,
**      create a new line with the index we found, and return Status_FoundLine.
**      However, if not found, it returns Status_Continue
**      to allow the loop to continue until it finds an EOF or line separator.
**
** * If it occurs an error in malloc, function will return a NULL pointer.
**   we can use it for handing error in main function.
*/

static int			read_line(t_reader *reader, char **line)
{
	ssize_t			index;
	char			*buf;

	buf = reader->buffer;
	index = ft_indexof(buf, LINE_SEPARATOR, reader->len);
	if (reader->eof)
		index = reader->len;
	if (index >= 0)
	{
		if (!(*line = malloc(1 + index)))
			return (Status_Error);
		ft_memcpy(*line, buf, index);
		(*line)[index] = '\0';
		reader->len -= (index + 1);
		if (reader->len > 0)
			ft_memmove(&buf[0], &buf[index + 1], reader->len);
		return (reader->eof ? Status_EOF : Status_FoundLine);
	}
	return (Status_Continue);
}

int					get_next_line(int fd, char **line)
{
	static t_reader	*readers[FD_MAX];
	char			buffer[BUFFER_SIZE];
	ssize_t			len;
	int				status;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (Return_Error);
	if (readers[fd] == NULL && !(readers[fd] = new_reader()))
		return (Return_Error);
	while ((status = read_line(readers[fd], line)) == Status_Continue)
	{
		if ((len = read(fd, buffer, BUFFER_SIZE)) < 0)
			break ;
		if (!append_buffer(readers[fd], buffer, len))
			break ;
		if (len == 0)
			readers[fd]->eof = TRUE;
	}
	if (status == Status_FoundLine)
		return (Return_FoundLine);
	if (readers[fd]->buffer)
		free(readers[fd]->buffer);
	free(readers[fd]);
	readers[fd] = NULL;
	return (len == 0 ? Return_EOF : Return_Error);
}
