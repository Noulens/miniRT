/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_vect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:37:50 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/24 13:37:54 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putfloat_fd(int n, int fd)
{
	int	i;
	int	tab[12];

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n != 0)
	{
		i = 0;
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		while (n > 0)
		{
			tab[i++] = n % 10 + 48;
			if (i == 2)
				tab[i++] = '.';
			n /= 10;
		}
		while (--i >= 0)
			write(1, &tab[i], 1);
	}
	else
		write(fd, "0", 1);
}



void	ft_print_vect(float x, float y, float z, int fd)
{
	float	tab[3];
	int 	i;
	int 	n;

	x *= 100;
	y *= 100;
	z *= 100;
	if (x > 2147483647.0f || y > 2147483647.0f || z > 2147483647.0f
		|| x < -2147483648.0f || y < -2147483648.0f || z < -2147483648.0f)
		return (write(2, "overflow\n", 9), (void)0);
	else
	{
		i = -1;
		tab[0] = x;
		tab[1] = y;
		tab[2] = z;
		while (++i < 3)
		{
			n = (int)tab[i];
			ft_putfloat_fd(n, fd);
			if (i < 2)
				write(fd, " ", 1);
		}
	}
}
/*
#include <unistd.h>


int	main(void)
{
	ft_print_vect(0, -45.236, 789.2587, 1);
	return (0);
}*/
