/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:10:31 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/27 16:10:35 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_stdobj	*objnew(void *content, t_objtp type)
{
	t_stdobj	*first;

	first = (t_stdobj *)malloc(sizeof(t_stdobj));
	if (!first)
		return (NULL);
	first->obj = content;
	first->objtp = type;
	first->next = NULL;
	return (first);
}

void	objadd_front(t_stdobj **lst, t_stdobj *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

void	objclear(t_stdobj *lst)
{
	t_stdobj	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		if (lst->obj)
			free(lst->obj);
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}
