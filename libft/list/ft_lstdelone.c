/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 07:47:18 by smun              #+#    #+#             */
/*   Updated: 2020/10/03 17:16:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void				ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		if (del != NULL)
			del(lst->content);
		free(lst);
	}
}
