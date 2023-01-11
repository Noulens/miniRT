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

int	objadd_front(t_stdobj **lst, void *item, t_objtp type, int color)
{
	t_stdobj	*new_obj;
	t_stdobj	*tmp;
	static int	id;

	new_obj = malloc(sizeof(t_stdobj));
	if (!new_obj)
		return (ft_fprintf(2, "Error\nerror in malloc LL obj\n"), FAIL);
	new_obj->objtp = type;
	new_obj->obj = item;
	new_obj->next = NULL;
	new_obj->objid = ++id;
	new_obj->metacolor = color;
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

int	objlstsize(t_stdobj *lst)
{
	if (lst)
		return (objlstsize(lst->next) + 1);
	else
		return (0);
}

int	list_to_tab(t_scene *scn)
{
	t_stdobj	*tmp;
	size_t		idx;

	idx = scn->num_objects_in_scene;
	scn->objtab = (t_stdobj **)ft_calloc(sizeof(t_stdobj *), idx + 1);
	if (!scn->objtab)
		return (ft_fprintf(2, "Error\nlist_to_tab bad malloc"), FAIL);
	tmp = scn->objects;
	idx = 0;
	while (tmp != NULL)
	{
		scn->objtab[idx] = tmp;
		idx++;
		tmp = tmp->next;
	}
	return (SUCCESS);
}
