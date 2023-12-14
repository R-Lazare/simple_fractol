/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:42:00 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/14 14:57:07 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int	julia_calc(t_c c, t_c z0, t_data img)
{
	t_c		z;
	int		i;
	double	mod_sq;

	z.re = z0.re;
	z.img = z0.img;
	i = 0;
	mod_sq = 0;
	while (i < img.max_iter && mod_sq < 3)
	{
		z = sum_i(pow_i(z, img.power, img.burning_ship), c);
		mod_sq = module_sq(z);
		i++;
	}
	return (i);
}

int	julia(t_data img)
{
	double	x;
	double	y;
	int		m;
	t_c		c;

	x = 0;
	while (x <= img.width)
	{
		y = 0;
		while (y <= img.height)
		{
			c = (t_c){.re = img.c1, .img = img.c2};
			m = julia_calc(c, (t_c){.re = img.xmin + (x / img.width) * (img.xmax
						- img.xmin), .img = img.ymin + (y / img.height
						) * (img.ymax - img.ymin)}, img);
			my_pixel_put(&img, (int)x, (int)y, img.colorpalette[m]);
			y++;
		}
		x++;
	}
	return (0);
}

void	zoomplus(t_data *img)
{
	double	zoomfactor;
	double	width;
	double	height;

	zoomfactor = 2.0;
	img->zoom++;
	width = (img->xmax - img->xmin) / zoomfactor;
	height = (img->ymax - img->ymin) / zoomfactor;
	img->xmin = img->xmin + img->x0 * width;
	img->xmax = img->xmin + width;
	img->ymin = img->ymin + img->y0 * height;
	img->ymax = img->ymin + height;
}
