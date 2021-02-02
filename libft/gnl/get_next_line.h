/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:56:59 by smun              #+#    #+#             */
/*   Updated: 2021/01/09 01:02:01 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# ifndef LINE_SEPARATOR
#  define LINE_SEPARATOR '\n'
# endif

# ifndef FD_MAX
#  define FD_MAX 256
# endif

/*
** ============================================================================
**    Enums
** ============================================================================
*/

enum			e_status
{
	Status_Error = -1,
	Status_Continue = 0,
	Status_FoundLine = 1,
	Status_EOF = 2
};

enum			e_return
{
	Return_Error = -1,
	Return_EOF = 0,
	Return_FoundLine = 1
};

/*
** ============================================================================
**   Structures / Unions
** ============================================================================
*/

typedef struct	s_reader
{
	char		*buffer;
	ssize_t		len;
	t_bool		eof;
}				t_reader;

#endif
