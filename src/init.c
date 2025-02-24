/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:16:03 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 13:56:35 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		return (1);
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "Fractol");
	if (!fractal->win)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		return (1);
	}
	return (0);
}

int	init_image(t_fractal *fractal)
{
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		return (1);
	}
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bits_per_pixel,
			&fractal->line_length, &fractal->endian);
	return (0);
}

int	init_data(t_fractal *fractal)
{
	if (init_mlx(fractal) == 1)
		return (1);
	if (init_image(fractal) == 1)
		return (1);
	fractal->min_x = -2.0;
	fractal->max_x = 2.0;
	fractal->min_y = -1.5;
	fractal->max_y = 1.5;
	fractal->zoom = 1.0;
	fractal->max_iter = MAX_ITER_BASE;
	fractal->color_shift = 4;
	fractal->move_x = 0;
	fractal->move_y = 0;
	return (0);
}

void	cleanup_data(t_fractal *fractal)
{
	if (fractal->img)
		mlx_destroy_image(fractal->mlx, fractal->img);
	if (fractal->win)
		mlx_destroy_window(fractal->mlx, fractal->win);
	if (fractal->mlx)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
	}
}
