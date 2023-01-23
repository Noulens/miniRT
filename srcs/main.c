/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:12:29 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/23 17:18:19 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
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
	int k = -1;
	// t_light		*tmp2;
	// tmp2 = scene->lamp;	
	// while (tmp2)
	// {
	// 	printf("L:\npos: %f, %f, %f\nbrightness: %f\nrgb: %d, %d, %d\n",
	// 		tmp2->pos.x, tmp2->pos.y, tmp2->pos.z,
	// 		tmp2->brightness, get_r(tmp2->color),
	// 		get_g(tmp2->color), get_b(tmp2->color));
	// 	tmp2 = tmp2->next;
	// }
	while (++k < scene->num_lamps)
	{
		printf("L:\npos: %f, %f, %f\nbrightness: %f\nrgb: %d, %d, %d\n",
			scene->lamptab[k]->pos.x, scene->lamptab[k]->pos.y, scene->lamptab[k]->pos.z,
			scene->lamptab[k]->brightness, get_r(scene->lamptab[k]->color),
			get_g(scene->lamptab[k]->color), get_b(scene->lamptab[k]->color));
	}
	tmp = scene->objects;
	while (tmp)
	{
		if (tmp->objtp == SP)
		{
			sphere = (t_sp *)tmp->obj;
			printf("SP:\npos: %f, %f, %f\ndia: %f\nrgb: %d, %d, %d\n",
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
}*/

int	main(int argc, char **argv)
{
	t_scene	scn;

	if (scenevarinit(&scn), argc == 2 && rt_name_checker(argv[1])
		&& !parse(&scn, argv[1]))
	{
		win_launcher(&scn);
	}
	else
	{
		ft_fprintf(2, "Error\nUsage : ./miniRT <filename.rt>\n");
		des_minirt(&scn);
		return (1);
	}
	return (0);
}
