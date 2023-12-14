/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:32:10 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/14 14:49:22 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline t_c	mandelbrot_op(t_c z, t_c c, int burn)
{
	return (sum_i(pow_i(z, 2, burn), c));
}

static int	mandelbrot_calc(t_c c, t_data img)
{
	t_c		z;
	int		i;
	double	mod_sq;

	z = (t_c){.re = 0, .img = 0};
	i = 0;
	mod_sq = 0;
	while (i < img.max_iter && mod_sq < 3)
	{
		z = mandelbrot_op(z, c, img.burning_ship);
		mod_sq = module_sq(z);
		i++;
	}
	if (i == img.max_iter)
		return (i);
	return (i);
}

int	mandelbrot(t_data img)
{
	double	x;
	double	y;
	int		m;
	t_c		c;

	x = 0;
	while (x <= img.width - 1)
	{
		y = 0;
		while (y <= img.height - 1)
		{
			c = (t_c){.re = img.xmin + (x / img.width) * (img.xmax - img.xmin),
				.img = img.ymin + (y / img.height) * (img.ymax - img.ymin)};
			m = mandelbrot_calc(c, img);
			my_pixel_put(&img, (int)x, (int)y, img.colorpalette[m]);
			y++;
		}
		x++;
	}
	return (0);
}
