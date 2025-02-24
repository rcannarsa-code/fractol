/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:15:57 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 13:58:14 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	draw_mandelbrot(t_fractal *fractal)
{
	int			x;
	int			y;
	t_complex	c;
	int			iterations;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c = get_scaled_coordinate(fractal, x, y);
			iterations = iterate_mandelbrot(c, MAX_ITER);
			my_mlx_pixel_put(fractal, x, y, create_psychedelic_color(iterations,
					MAX_ITER, fractal->color_shift));
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

void	draw_julia(t_fractal *fractal)
{
	int			x;
	int			y;
	t_complex	z;
	int			iterations;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			z = get_scaled_coordinate(fractal, x, y);
			iterations = iterate_julia(z, fractal->julia_c, MAX_ITER);
			my_mlx_pixel_put(fractal, x, y, create_psychedelic_color(iterations,
					MAX_ITER, fractal->color_shift));
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

void	draw_celtic(t_fractal *fractal)
{
	int			x;
	int			y;
	t_complex	c;
	int			iterations;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c = get_scaled_coordinate(fractal, x, y);
			iterations = iterate_celtic(c, MAX_ITER);
			my_mlx_pixel_put(fractal, x, y, create_psychedelic_color(iterations,
					MAX_ITER, fractal->color_shift));
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

void	draw_burning_ship(t_fractal *fractal)
{
	int			x;
	int			y;
	t_complex	c;
	int			iterations;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c = get_scaled_coordinate(fractal, x, y);
			iterations = iterate_burning_ship(c, MAX_ITER);
			my_mlx_pixel_put(fractal, x, y, create_psychedelic_color(iterations,
					MAX_ITER, fractal->color_shift));
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

void	draw_fractal(t_fractal *fractal)
{
	if (fractal->fractal_type == 1)
		draw_mandelbrot(fractal);
	else if (fractal->fractal_type == 2)
		draw_julia(fractal);
	else if (fractal->fractal_type == 3)
		draw_celtic(fractal);
	else if (fractal->fractal_type == 4)
		draw_burning_ship(fractal);
}
