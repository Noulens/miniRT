/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:12:29 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/28 23:10:26 by hyunah           ###   ########.fr       */
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

// t_matrix4	ft_get_hat(t_vec3 rot)
// {
// 	t_matrix4 ret;

// 	init_matrix(&ret);
// 	ret.m[0][0] = 0;
// 	ret.m[0][1] = -rot.z;
// 	ret.m[0][2] = rot.y;
// 	ret.m[1][0] = rot.z;
// 	ret.m[1][1] = 0;
// 	ret.m[1][2] = -rot.x;
// 	ret.m[2][0] = -rot.y;
// 	ret.m[2][1] = rot.x;
// 	ret.m[2][2] = 0;
// }
t_vec3	rotate_from_axis_angle(t_vec3 vector, t_vec3 axis, float angle)
{
	t_vec3	d;
	t_vec3	r;
	t_vec3	rcos;
	t_vec3	axiscross;
	t_vec3	ssin;
	float	tmp;


	axis = vec_normalize(axis);
	tmp = vec_dot(axis, vector);
	d = vec_scale(axis, tmp);
	r = vec_sub(vector, d);
	rcos = vec_scale(r, cosf(angle));
	axiscross = vec_cross(axis, r);
	ssin = vec_scale(axiscross, sinf(angle));
	return (vec_add(vec_add(ssin, rcos), d));
}

int	main(int argc, char **argv)
{
	t_scene	scn;

	if (scenevarinit(&scn), argc == 2 && rt_name_checker(argv[1])
		&& !parse(&scn, argv[1]))
	{
		// t_vec3	axis_u;
		// t_vec3	axis_v;
		// t_vec3	normal;

		// normal = set_vec(0, 1, 0);


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

/*
		t_vec3	a = set_vec(1, 2, 3);
		t_vec3	b = set_vec(1, 2, 3);
		t_vec3	rot = set_vec(30, 20, 10);
		t_vec3	vec_null;
		t_matrix4	rot_m;

		vec_null = set_vec(0, 0, 0);
		rot_m = set_transform2(&vec_null, &rot);
		matrix_vec_mult(rot_m, &a);
		matrix_vec_mult(rot_m, &b);
		printf("\nresult : %f %f %f\n", a.x, a.y, a.z);
		rot_m = inverse(rot_m);
		matrix_vec_mult(rot_m, &b);
		printf("\nresult : %f %f %f\n", b.x, b.y, b.z);

	t_vec3	a = set_vec(0, 1, 0);
	t_vec3	b = set_vec(0.5, 0.5, 0);

	t_vec3	axis;
	float	angle;
	float	dot;
	t_vec3	ret;

	printf("a : \n");
	a = vec_normalize(a);
	print_vec(&a);
	b = vec_normalize(b);
	printf("b : \n");
	print_vec(&b);
	printf("\n");
	axis = vec_cross(vec_normalize(a), vec_normalize(b));
	axis = vec_normalize(axis);
	dot = vec_dot(vec_normalize(a), vec_normalize(b));
	printf("dot(a, b) : %f\n", dot);
	angle = acosf(vec_dot(vec_normalize(a), vec_normalize(b)));
	// vec_null = set_vec(0, 0, 0);
	printf("axis of rotation : %f %f %f\n", axis.x, axis.y, axis.z);
	printf("angle(radian) between a, b : %f, (degree) : %f\n", angle, to_degree(angle));
	ret = rotate_from_axis_angle(a, axis, angle);
	printf("\nresult : %f %f %f\n", ret.x, ret.y, ret.z);
*/