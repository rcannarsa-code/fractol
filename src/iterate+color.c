/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate+color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:43:13 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/19 14:57:57 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	create_psychedelic_color(int iterations, int max_iter, int color_shift)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations == max_iter)
		return (0xFFFFFF);
	t = (double)iterations / max_iter;
	t = t * t;
	r = sin(0.3 * t * 20 + color_shift) * 127;
	g = sin(0.3 * t * 20 + 2 + color_shift) * 127;
	b = sin(0.3 * t * 20 + 4 + color_shift) * 127;
	r = (r + 127) * t;
	g = (g + 127) * t;
	b = (b + 127) * t;
	return (create_trgb(0, r, g, b));
}
