/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 04:48:07 by smun              #+#    #+#             */
/*   Updated: 2020/10/04 15:46:44 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*back;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			back = ft_lstlast(*lst);
			back->next = new;
		}
	}
}
