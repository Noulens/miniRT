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

int objadd_front(t_stdobj **lst, void *item, t_objtp type)
{
	t_stdobj	*new_obj;
	t_stdobj	*tmp;

	new_obj = malloc(sizeof(t_stdobj));
	if (!new_obj)
	{
		ft_fprintf(2, "Error\nerror in malloc LL obj\n");
		return (FAIL);
	}
	new_obj->objtp = type;
	new_obj->obj = item;
	new_obj->next = NULL;
	if (!(*lst))
		*lst = new_obj;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_obj;
	}
	return (SUCCESS);
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
