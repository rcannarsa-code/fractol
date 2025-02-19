/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:15:53 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/19 11:40:54 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_complex	complex_add(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real + b.real;
	result.imag = a.imag + b.imag;
	return (result);
}

t_complex	complex_multiply(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real * b.real - a.imag * b.imag;
	result.imag = a.real * b.imag + a.imag * b.real;
	return (result);
}

double	complex_abs(t_complex c)
{
	return (sqrt(c.real * c.real + c.imag * c.imag));
}

t_complex	get_scaled_coordinate(t_fractal *fractal, int x, int y)
{
	t_complex	coord;

	coord.real = fractal->min_x + (x * (fractal->max_x - fractal->min_x))
		/ WIDTH + fractal->move_x;
	coord.imag = fractal->min_y + (y * (fractal->max_y - fractal->min_y))
		/ HEIGHT + fractal->move_y;
	return (coord);
}
