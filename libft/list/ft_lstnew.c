/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 04:38:37 by smun              #+#    #+#             */
/*   Updated: 2020/10/03 04:47:17 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list				*ft_lstnew(void *content)
{
	t_list			*lst;

	if ((lst = malloc(sizeof(t_list))))
	{
		lst->content = content;
		lst->next = NULL;
	}
	return (lst);
}
