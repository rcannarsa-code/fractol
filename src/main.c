/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:16:06 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 13:57:34 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void	print_instructions(void)
{
	ft_printf("\nControls:\n");
	ft_printf("Arrow keys: Move view\n");
	ft_printf("Mouse wheel: Zoom in/out\n");
	ft_printf("C key: Shift colors\n");
	ft_printf("ESC or X: Exit\n\n");
}

static void	set_julia_params(t_fractal *fractal)
{
	fractal->fractal_type = 2;
	fractal->julia_c.real = -0.7;
	fractal->julia_c.imag = 0.27015;
}

static int	check_fractal_type(char *type, t_fractal *fractal)
{
	if (ft_strncmp(type, "mandelbrot", 10) == 0)
		fractal->fractal_type = 1;
	else if (ft_strncmp(type, "julia", 5) == 0)
		set_julia_params(fractal);
	else if (ft_strncmp(type, "celtic", 6) == 0)
		fractal->fractal_type = 3;
	else if (ft_strncmp(type, "burning_ship", 11) == 0)
		fractal->fractal_type = 4;
	else
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (argc < 2)
	{
		ft_printf("Usage: %s [mandelbrot/julia/celtic/burning_ship]\n",
			argv[0]);
		return (1);
	}
	if (init_data(&fractal) == 1)
		return (1);
	if (check_fractal_type(argv[1], &fractal))
	{
		cleanup_data(&fractal);
		ft_printf("Invalid fractal type\n");
		return (1);
	}
	print_instructions();
	draw_fractal(&fractal);
	setup_hooks(&fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
