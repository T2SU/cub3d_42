/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:17:59 by smun              #+#    #+#             */
/*   Updated: 2020/10/04 16:15:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if ((mem = malloc(count * size)))
		ft_bzero(mem, count * size);
	return (mem);
}
