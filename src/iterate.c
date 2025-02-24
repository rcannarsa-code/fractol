/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:43:13 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 13:56:38 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
{
	char	*dst;

	dst = fractal->addr + (y * fractal->line_length + x
			* (fractal->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	iterate_julia(t_complex z, t_complex c, int max_iter)
{
	int	i;

	i = -1;
	while (++i < max_iter && complex_abs(z) <= 2.0)
		z = complex_add(complex_multiply(z, z), c);
	return (i);
}

int	iterate_mandelbrot(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;

	z.real = 0;
	z.imag = 0;
	i = -1;
	while (++i < max_iter && complex_abs(z) <= 2.0)
		z = complex_add(complex_multiply(z, z), c);
	return (i);
}

int	iterate_celtic(t_complex c, int max_iter)
{
	t_complex	z;
	double		temp;
	int			i;

	z.real = 0;
	z.imag = 0;
	i = -1;
	while (++i < max_iter && complex_abs(z) <= 2.0)
	{
		temp = fabs(z.real * z.real - z.imag * z.imag) + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
	}
	return (i);
}

int	iterate_burning_ship(t_complex c, int max_iter)
{
	t_complex	z;
	double		temp;
	int			i;

	z.real = 0;
	z.imag = 0;
	i = -1;
	while (++i < max_iter && complex_abs(z) <= 2.0)
	{
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = fabs(2 * z.real * z.imag) + c.imag;
		z.real = temp;
	}
	return (i);
}
