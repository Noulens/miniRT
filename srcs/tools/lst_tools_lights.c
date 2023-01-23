/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:20:25 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/23 17:15:46 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	objadd_front_l(t_light **lst)
{
	t_light		*new_obj;
	static int	idl;

	new_obj = malloc(sizeof(t_light));
	if (!new_obj)
		return (ft_fprintf(2, "Error\nerror in malloc LL lamp\n"), FAIL);
	new_obj->idl = idl++;
	new_obj->next = NULL;
	if (!(*lst))
		*lst = new_obj;
	else
	{
		new_obj->next = *lst;
		*lst = new_obj;
	}
	return (SUCCESS);
}

void	lpdes_l(t_light *lst)
{
	t_light	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}

int	objlstsize_l(t_light *lst)
{
	if (lst)
		return (objlstsize_l(lst->next) + 1);
	else
		return (0);
}

int	list_to_tab_l(t_scene *scn)
{
	t_light	*tmp;
	size_t	idx;

	idx = scn->num_lamps;
	scn->lamptab = (t_light **)ft_calloc(sizeof(t_light *), idx + 8);
	if (!scn->lamptab)
		return (ft_fprintf(2, "Error\nlist_to_tab_l bad malloc"), FAIL);
	tmp = scn->lamp;
	idx = 0;
	while (tmp != NULL)
	{
		scn->lamptab[idx] = tmp;
		idx++;
		tmp = tmp->next;
	}
	return (SUCCESS);
}
