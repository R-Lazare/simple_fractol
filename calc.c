/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:55:10 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/14 14:43:08 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline double	custom_fabs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

inline t_c	sum_i(t_c a, t_c b)
{
	return ((t_c){.re = (a.re + b.re), .img = (a.img + b.img)});
}

inline double	module_sq(t_c z)
{
	return (z.re * z.re + z.img * z.img);
}

inline t_c	pow_i(t_c z, int power, int burn)
{
	t_c	z0;

	if (burn)
		z = (t_c){.re = custom_fabs(z.re), .img = custom_fabs(z.img)};
	z0 = z;
	while (power-- > 1)
		z = (t_c){.re = z.re * z0.re - z.img * z0.img, .img = z0.re * z.img
			+ z0.img * z.re};
	return (z);
}

int	freeall(t_data *img)
{
	if (img->arena)
	{
		arena_destroy(img->arena);
		if (img->img)
		{
			mlx_destroy_image(img->mlx, img->img);
			if (img->win)
				mlx_destroy_window(img->mlx, img->win);
			if (img->mlx)
				mlx_destroy_display(img->mlx);
			if (img->mlx)
				free(img->mlx);
		}
	}
	exit(0);
	return (0);
}
