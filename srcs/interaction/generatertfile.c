/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generatertfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:03:26 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/30 19:03:29 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	save_plan(const t_scene *scn, int fd, int k)
{
	t_pl	*pl;

	pl = (t_pl *)scn->objtab[k]->obj;
	ft_fprintf(fd, "\npl ");
	ft_putfloat_fd(pl->translate.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(pl->translate.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(pl->translate.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(pl->orientation.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(pl->orientation.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(pl->orientation.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(get_r(pl->color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_g(pl->color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_b(pl->color), fd);
}

void	save_cy(const t_scene *scn, int fd, int k)
{
	t_cy	*cy;

	cy = (t_cy *)scn->objtab[k]->obj;
	ft_fprintf(fd, "\ncy ");
	ft_putfloat_fd(cy->pos.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(cy->pos.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(cy->pos.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(cy->orientation.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(cy->orientation.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(cy->orientation.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(cy->diameter, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(cy->height, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(get_r(cy->color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_g(cy->color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_b(cy->color), fd);
}

void	save_co(const t_scene *scn, int fd, int k)
{
	t_co	*co;

	co = (t_co *)scn->objtab[k]->obj;
	ft_fprintf(fd, "\nco ");
	ft_putfloat_fd(co->pos.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(co->pos.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(co->pos.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(co->orientation.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(co->orientation.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(co->orientation.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(co->rad, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(co->height, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(get_r(co->color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_g(co->color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_b(co->color), fd);
}

void	save_sp(const t_scene *scn, int fd, int k)
{
	t_sp	*sp;

	sp = (t_sp *)scn->objtab[k]->obj;
	ft_fprintf(fd, "\nsp ");
	ft_putfloat_fd(sp->pos.x, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(sp->pos.y, 2, fd);
	ft_putchar_fd(',', fd);
	ft_putfloat_fd(sp->pos.z, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putfloat_fd(sp->diameter, 2, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(get_r(sp->color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_g(sp->color), fd);
	ft_putchar_fd(',', fd);
	ft_putnbr_fd(get_b(sp->color), fd);
}

void	save_scene(t_scene *scn)
{
	int			fd;
	static int	v;
	char		*name;
	char		*save;

	save = ft_itoa(v++);
	if (!save)
		return (ft_fprintf(2, "Error\ncould not save\n"), (void)0);
	name = ft_strjoin(save, ".rt");
	if (!name)
		return (free(save), ft_fprintf(2, "Error\ncould not save\n"), (void)0);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(name);
		free(save);
		return (ft_fprintf(2, "Error\ncould not save\n"), (void)0);
	}
	save_cam(scn, fd);
	save_lamp(scn, fd);
	save_objs(scn, fd);
	free(name);
	free(save);
	close (fd);
	ft_fprintf(2, "scene saved successfully!!!\n");
}
