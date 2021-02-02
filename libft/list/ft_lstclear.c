/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 07:51:29 by smun              #+#    #+#             */
/*   Updated: 2020/10/03 07:56:57 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void				ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list			*elem;
	t_list			*b;

	if (lst)
	{
		elem = *lst;
		while (elem != NULL)
		{
			if (del != NULL)
				del(elem->content);
			b = elem;
			elem = elem->next;
			free(b);
		}
	}
	*lst = NULL;
}
