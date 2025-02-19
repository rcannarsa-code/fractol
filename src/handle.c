/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:25:28 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/19 14:49:47 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	handle_close(t_fractal *fractal)
{
	cleanup_data(fractal);
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_fractal *fractal)
{
	if (keycode == KEY_ESC)
	{
		cleanup_data(fractal);
		exit(0);
	}
	else if (keycode == KEY_C)
		shift_colors(fractal);
	else if (keycode >= KEY_LEFT && keycode <= KEY_DOWN)
		move_view(keycode, fractal);
	draw_fractal(fractal);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	double	x_before_zoom;
	double	y_before_zoom;
	double	zoom_factor;
	double	width;

	x_before_zoom = fractal->min_x + (x * (fractal->max_x - fractal->min_x))
		/ WIDTH;
	y_before_zoom = fractal->min_y + (y * (fractal->max_y - fractal->min_y))
		/ HEIGHT;
	if (button == 4)
		zoom_factor = 0.9;
	else if (button == 5)
		zoom_factor = 1.1;
	else
		return (0);
	width = fractal->max_x - fractal->min_x;
	if (width * zoom_factor < 1e-13)
		return (0);
	update_zoom(fractal, zoom_factor, x_before_zoom, y_before_zoom);
	fractal->max_iter = (int)(MAX_ITER_BASE * (1 + 2 * log10(1 / width)));
	if (fractal->max_iter < MAX_ITER_BASE)
		fractal->max_iter = MAX_ITER_BASE;
	draw_fractal(fractal);
	return (0);
}
