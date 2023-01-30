/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generatefile2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:02:54 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/30 19:02:58 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	save_objs(const t_scene *scn, int fd)
{
	int	k;

	k = -1;
	while (++k < scn->num_objects_in_scene)
	{
		if (scn->objtab[k]->objtp == PL)
		{
			save_plan(scn, fd, k);
		}
		else if (scn->objtab[k]->objtp == CY)
		{
			save_cy(scn, fd, k);
		}
		else if (scn->objtab[k]->objtp == CO)
		{
			save_co(scn, fd, k);
		}
		else if (scn->objtab[k]->objtp == SP)
		{
			save_sp(scn, fd, k);
		}
	}
}

void	save_lamp(const t_scene *scn, int fd)
{
	int	k;

	k = -1;
	while (++k < scn->num_lamps)
	{
		ft_fprintf(fd, "\nL ");
		ft_putfloat_fd(scn->lamptab[k]->pos.x, 2, fd);
		ft_putchar_fd(',', fd);
		ft_putfloat_fd(scn->lamptab[k]->pos.y, 2, fd);
		ft_putchar_fd(',', fd);
		ft_putfloat_fd(scn->lamptab[k]->pos.z, 2, fd);
		ft_putchar_fd(' ', fd);
		ft_putfloat_fd(scn->lamptab[k]->brightness, 2, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(get_r(scn->lamptab[k]->color), fd);
		ft_putchar_fd(',', fd);
		ft_putnbr_fd(get_g(scn->lamptab[k]->color), fd);
		ft_putchar_fd(',', fd);
		ft_putnbr_fd(get_b(scn->lamptab[k]->color), fd);
	}
}

void	save_cam(const t_scene *scn, int fd)
{
	ft_fprintf(fd, "C ");
	ft_putfloat_fd(scn->cam.translate.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(scn->cam.translate.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(scn->cam.translate.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(scn->cam.orientation.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(scn->cam.orientation.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(scn->cam.orientation.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(scn->cam.fov_w, 2, fd);
	ft_fprintf(fd, "\nA ");
	ft_putfloat_fd(scn->alight.al, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(get_r(scn->alight.color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_g(scn->alight.color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_b(scn->alight.color), fd);
}
