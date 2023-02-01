/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:02:42 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/30 19:02:47 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

int	copy_co(t_scene *scn, const int tgt)
{
	t_co	*cyl;
	t_co	*copy;

	cyl = (t_co *)scn->objtab[tgt]->obj;
	copy = (t_co *)malloc(sizeof(t_co));
	if (!copy)
		return (ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	copy->pos = vec_add(cyl->pos, set_vec(0.2f, 0.2f, 0.2f));
	copy->orientation = cyl->orientation;
	copy->height = cyl->height;
	copy->rad = cyl->rad;
	copy->color = cyl->color;
	copy->rotate = cyl->rotate;
	copy->translate = cyl->translate;
	if (objadd_front(&scn->objects, copy, CO, copy->color))
		return (free (copy), ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	free(scn->objtab);
	scn->objtab = NULL;
	if (list_to_tab(scn))
		return (ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	scn->num_objects_in_scene++;
	return (SUCCESS);
}

int	copy_cy(t_scene *scn, const int tgt)
{
	t_cy	*cyl;
	t_cy	*copy;

	cyl = (t_cy *)scn->objtab[tgt]->obj;
	copy = (t_cy *)malloc(sizeof(t_cy));
	if (!copy)
		return (ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	copy->pos = vec_add(cyl->pos, set_vec(0.2f, 0.2f, 0.2f));
	copy->orientation = cyl->orientation;
	copy->height = cyl->height;
	copy->diameter = cyl->diameter;
	copy->color = cyl->color;
	copy->rotate = cyl->rotate;
	copy->translate = cyl->translate;
	if (objadd_front(&scn->objects, copy, CY, copy->color))
		return (free (copy), ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	free(scn->objtab);
	scn->objtab = NULL;
	if (list_to_tab(scn))
		return (ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	scn->num_objects_in_scene++;
	return (SUCCESS);
}

int	copy_pl(t_scene *scn, const int tgt)
{
	t_pl	*pl;
	t_pl	*copy;

	pl = (t_pl *)scn->objtab[tgt]->obj;
	copy = (t_pl *)malloc(sizeof(t_pl));
	if (!copy)
		return (ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	copy->pos = pl->pos;
	copy->orientation = pl->orientation;
	copy->color = pl->color;
	copy->rotate = pl->rotate;
	copy->translate = pl->translate;
	if (objadd_front(&scn->objects, copy, PL, copy->color))
		return (free (copy), ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	free(scn->objtab);
	scn->objtab = NULL;
	if (list_to_tab(scn))
		return (ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	scn->num_objects_in_scene++;
	return (SUCCESS);
}

int	copy_sp(t_scene *scn, const int tgt)
{
	t_sp	*sp;
	t_sp	*copy;

	sp = (t_sp *)scn->objtab[tgt]->obj;
	copy = (t_sp *)malloc(sizeof(t_sp));
	if (!copy)
		return (ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	copy->pos = sp->pos;
	copy->diameter = sp->diameter;
	copy->color = sp->color;
	copy->rotate = sp->rotate;
	copy->translate = sp->translate;
	if (objadd_front(&scn->objects, copy, SP, copy->color))
		return (free (copy), ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	free(scn->objtab);
	scn->objtab = NULL;
	if (list_to_tab(scn))
		return (ft_fprintf(2, "Copy fail, bad malloc\n"), FAIL);
	scn->num_objects_in_scene++;
	return (SUCCESS);
}

int	copy_paste(t_scene *scn)
{
	int	tgt;
	int	res;

	tgt = scn->target;
	res = SUCCESS;
	if (tgt == -1 || tgt == -2)
	{
		ft_fprintf(2, "Error\nno object selected\n");
		return (FAIL);
	}
	else
	{
		if (scn->objtab[tgt - 1]->objtp == PL)
			res = copy_pl(scn, tgt - 1);
		else if (scn->objtab[tgt - 1]->objtp == SP)
			res = copy_sp(scn, tgt - 1);
		else if (scn->objtab[tgt - 1]->objtp == CY)
			res = copy_cy(scn, tgt - 1);
		else if (BONUS == TRUE && scn->objtab[tgt - 1]->objtp == CO)
			res = copy_co(scn, tgt - 1);
		if (res == FAIL)
			ft_closebutton((void *)scn);
	}
	ft_fprintf(2, "Copy successfull !!!\n");
	return (SUCCESS);
}
