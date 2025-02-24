/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:16:00 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 13:56:33 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	move_view(int keycode, t_fractal *fractal)
{
	double	move_step;

	move_step = 0.3 * fractal->zoom;
	if (keycode == KEY_LEFT)
		fractal->move_x -= move_step;
	else if (keycode == KEY_RIGHT)
		fractal->move_x += move_step;
	else if (keycode == KEY_UP)
		fractal->move_y -= move_step;
	else if (keycode == KEY_DOWN)
		fractal->move_y += move_step;
}

void	shift_colors(t_fractal *fractal)
{
	fractal->color_shift += 1;
	if (fractal->color_shift > 360)
		fractal->color_shift = 0;
}

void	update_zoom(t_fractal *fractal, double zoom_factor, double x_before,
		double y_before)
{
	double	new_width;
	double	new_height;

	new_width = (fractal->max_x - fractal->min_x) * zoom_factor;
	new_height = (fractal->max_y - fractal->min_y) * zoom_factor;
	fractal->zoom = new_width - new_height;
	fractal->min_x = x_before - (x_before - fractal->min_x) * zoom_factor;
	fractal->max_x = fractal->min_x + new_width;
	fractal->min_y = y_before - (y_before - fractal->min_y) * zoom_factor;
	fractal->max_y = fractal->min_y + new_height;
}

void	setup_hooks(t_fractal *fractal)
{
	mlx_hook(fractal->win, 2, 1L << 0, handle_keypress, fractal);
	mlx_hook(fractal->win, 17, 0, handle_close, fractal);
	mlx_mouse_hook(fractal->win, handle_mouse, fractal);
}
