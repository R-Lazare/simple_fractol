/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:32:00 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/14 14:55:31 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	refresh_image(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	img->current_fractal(*img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int	key_hook_arrows(int keycode, t_data *img)
{
	if (keycode == 65362)
	{
		img->ymin = img->ymin - 0.1 * (1 / cosh(pow(img->zoom, 0.75)));
		img->ymax = img->ymax - 0.1 * (1 / cosh(pow(img->zoom, 0.75)));
	}
	if (keycode == 65364)
	{
		img->ymin = img->ymin + 0.1 * (1 / cosh(pow(img->zoom, 0.75)));
		img->ymax = img->ymax + 0.1 * (1 / cosh(pow(img->zoom, 0.75)));
	}
	if (keycode == 65361)
	{
		img->xmin = img->xmin - 0.1 * (1 / cosh(pow(img->zoom, 0.75)));
		img->xmax = img->xmax - 0.1 * (1 / cosh(pow(img->zoom, 0.75)));
	}
	if (keycode == 65363)
	{
		img->xmin = img->xmin + 0.1 * (1 / cosh(pow(img->zoom, 0.75)));
		img->xmax = img->xmax + 0.1 * (1 / cosh(pow(img->zoom, 0.75)));
	}
	return (0);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 98)
		img->burning_ship = !img->burning_ship;
	if (keycode == 65307)
		freeall(img);
	if (keycode == 65451 && img->max_iter < 190)
		img->max_iter += 20;
	if (keycode == 65453)
		img->max_iter -= 5;
	if (img->max_iter < 1)
		img->max_iter = 1;
	if (keycode == 51 || keycode == 38)
		img->c2 += 0.04;
	if (keycode == 52 || keycode == 233)
		img->c2 -= 0.04;
	if (keycode == 49 || keycode == 34)
		img->c1 += 0.04;
	if (keycode == 50 || keycode == 39)
		img->c1 -= 0.04;
	else
		key_hook_arrows(keycode, img);
	img->colorpalette = colors(img->max_iter, *img);
	refresh_image(img);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *img)
{
	double	zoomfactor;
	double	width;
	double	height;

	zoomfactor = 2.0;
	img->x0 = (double)x / img->width;
	img->y0 = (double)y / img->height;
	if (button == 4)
		zoomplus(img);
	else if (button == 5 && img->zoom > 0)
	{
		img->zoom--;
		width = (img->xmax - img->xmin) * zoomfactor;
		height = (img->ymax - img->ymin) * zoomfactor;
		img->xmin = img->xmin - img->x0 * (width - (img->xmax - img->xmin));
		img->xmax = img->xmin + width;
		img->ymin = img->ymin - img->y0 * (height - (img->ymax - img->ymin));
		img->ymax = img->ymin + height;
	}
	refresh_image(img);
	return (0);
}
