/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:12:29 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/24 10:33:00 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_objects_infos(t_scene *scene)
{
	t_stdobj	*tmp;
	t_sp		*sphere;
	t_cy		*cylinder;
	t_pl		*plan;

	printf("A:\nal: %f\nrgb: %d, %d, %d\n", scene->alight.al,
		get_r(scene->alight.color), get_g(scene->alight.color),
		get_b(scene->alight.color));
	printf("C:\npos: %f, %f, %f\norient: %f, %f, %f\nfov: %f\n",
		scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z,
		scene->cam.orientation.x, scene->cam.orientation.y,
		scene->cam.orientation.z, scene->cam.fov_w);
	printf("L:\npos: %f, %f, %f\nbrightness: %f\nrgb: %d, %d, %d\n",
		scene->light.pos.x, scene->light.pos.y, scene->light.pos.z,
		scene->light.brightness, get_r(scene->light.color),
		get_g(scene->light.color), get_b(scene->light.color));
	tmp = scene->objects;
	while (tmp)
	{
		if (tmp->objtp == SP)
		{
			sphere = (t_sp *)tmp->obj;
			printf("SP:\npos: %f, %f, %f\ndia: %f\nrgb: %d, %d, %d",
				sphere->pos.x, sphere->pos.y, sphere->pos.z,
				sphere->diameter,
				get_r(sphere->color), get_g(sphere->color),
				get_b(sphere->color));
		}
		else if (tmp->objtp == PL)
		{
			plan = (t_pl *)tmp->obj;
			printf("PL:\ncoord: %f, %f, %f\n", plan->pos.x, plan->pos.y,
				plan->pos.z);
			printf("orientation %f, %f, %f\n", plan->orientation.x,
				plan->orientation.y, plan->orientation.z);
			printf("color: %d, %d, %d\n", get_r(plan->color),
				get_g(plan->color), get_b(plan->color));
		}
		else if (tmp->objtp == CY)
		{
			cylinder = (t_cy *)tmp->obj;
			printf("CY:\npos: %f, %f, %f\norientation: %f, %f, %f\n"
				"dia: %f\nheight: %f\nrgb: %d, %d, %d\n", cylinder->pos.x,
				cylinder->pos.y, cylinder->pos.z, cylinder->orientation.x,
				cylinder->orientation.y, cylinder->orientation.z,
				cylinder->diameter, cylinder->height,
				get_r(cylinder->color), get_g(cylinder->color),
				get_b(cylinder->color));
		}
		tmp = tmp->next;
	}
	printf(YELLOW"\nnb of objects: %d\n"RESET, scene->num_objects_in_scene);
}

int	main(int argc, char **argv)
{
	t_scene	scn;

	scn.objects = NULL;
	if (argc == 2 && rt_name_checker(argv[1]) && !parse(&scn, argv[1]))
	{
		print_objects_infos(&scn);
		win_launcher(&scn);
	}
	else
	{
		objclear(scn.objects);
		exit(EXIT_FAILURE);
	}
	return (0);
}
