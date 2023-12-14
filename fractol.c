/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:06:12 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/14 15:09:00 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	main_mandelbrot(t_data img)
{
	img.width = 900;
	img.height = img.width * 1;
	img.xmin = -2;
	img.power = 2;
	img.max_iter = 80;
	img.xmax = 1;
	img.colorint = 7;
	img.ymin = -1;
	img.ymax = 1;
	img.burning_ship = 0;
	img.x0 = (img.xmax - img.xmin) / 2;
	img.y0 = (img.ymax - img.ymin) / 2;
	img.colorset = getlist(img.colorint, img, 1000);
	img.colorpalette = colors(img.max_iter, img);
	img.current_fractal = &mandelbrot;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.width, img.height, "Mandelbrot");
	img.img = mlx_new_image(img.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	img.current_fractal(img);
	mlx_mouse_hook(img.win, mouse_hook, &img);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_hook(img.win, 17, 0, freeall, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(img.mlx);
}

void	main_julia(t_data img)
{
	img.width = 1200;
	img.height = img.width * 1;
	img.xmin = -2;
	img.max_iter = 40;
	img.xmax = 2;
	img.colorint = 7;
	img.ymin = -2;
	img.ymax = 2;
	img.power = 2;
	img.x0 = (img.xmax - img.xmin) / 2;
	img.y0 = (img.ymax - img.ymin) / 2;
	img.colorset = getlist(img.colorint, img, 10000000);
	img.colorpalette = colors(img.max_iter, img);
	img.burning_ship = 0;
	img.current_fractal = &julia;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.width, img.height, "Julia");
	img.img = mlx_new_image(img.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	img.current_fractal(img);
	mlx_mouse_hook(img.win, mouse_hook, &img);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_hook(img.win, 17, 0, freeall, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(img.mlx);
}

int	check_args(char *c1, char *c2)
{
	int	i;

	i = 0;
	while (c1[i])
	{
		if (!ft_isdigit(c1[i]) && c1[i] != '.' && c1[i] != '-')
			return (0);
		i++;
	}
	i = 0;
	while (c2[i])
	{
		if (!ft_isdigit(c2[i]) && c2[i] != '.' && c2[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	img;

	img.arena = arena_init(2147483647);
	if (argc == 1)
		write(1, "Usage: ./fractol [fractalname] [c1] [c2]\n", 57);
	else if (!ft_strcmp(argv[1], "mandelbrot") && argc == 2)
		main_mandelbrot(img);
	else if (!ft_strcmp(argv[1], "julia") && argc == 4 && check_args(argv[2],
			argv[3]))
	{
		img.c1 = ft_atod(argv[2]);
		img.c2 = ft_atod(argv[3]);
		main_julia(img);
	}
	else if (!ft_strcmp(argv[1], "burningship") && argc == 2)
	{
		img.burning_ship = 1;
		main_mandelbrot(img);
	}
	else
		write(1, "Usage: ./fractol [fractalname] [c1] [c2]\n", 57);
	return (0);
}
