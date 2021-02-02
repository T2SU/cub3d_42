/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_list_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:21:01 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 14:52:26 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include <libft.h>

void			util_lstdel_find(t_game *g, t_list *del)
{
	t_list		*lst;
	t_list		*before;

	if (!del)
		return ;
	before = NULL;
	lst = g->map.ent;
	while (lst && lst != del)
	{
		before = lst;
		lst = lst->next;
	}
	if (!lst)
		return ;
	if (before)
		before->next = lst->next;
	else
		g->map.ent = lst->next;
	ft_lstdelone(del, &free);
}
