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

int	main(int argc, char **argv)
{
	t_scene	scn;

	scn.objects = NULL;
	if (argc == 2 && rt_name_checker(argv[1]) && !parse(&scn, argv[1]))
		win_launcher(&scn);
	else
	{
		objclear(scn.objects);
		exit(EXIT_FAILURE);
	}
	return (0);
}
