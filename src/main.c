/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:16:06 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/25 18:40:59 by rcannars         ###   ########.fr       */
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

static int check_exact_match(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i])
        i++;
    return (str1[i] == str2[i]);
}

static int check_fractal_type(char *type, t_fractal *fractal, int argc, char **argv)
{
    if (check_exact_match(type, "mandelbrot"))
        fractal->fractal_type = MANDELBROT;
    else if (check_exact_match(type, "julia"))
    {
        set_julia_params(fractal);
        parse_julia_params(fractal, argc, argv);
    }
    else if (check_exact_match(type, "celtic"))
        fractal->fractal_type = CELTIC;
    else if (check_exact_match(type, "burning_ship"))
        fractal->fractal_type = BURNING_SHIP;
    else
        return (1);
    return (0);
}

static void print_usage(char *program_name)
{
    ft_printf("Usage: %s [fractal_type] [parameters]\n\n", program_name);
    ft_printf("Fractal types:\n");
    ft_printf("  mandelbrot\n");
    ft_printf("  julia [real] [imaginary]\n");
    ft_printf("  celtic\n");
    ft_printf("  burning_ship\n");
}

int main(int argc, char **argv)
{
    t_fractal fractal;
    
    if (argc < 2)
    {
        print_usage(argv[0]);
        return (1);
    }
    if (init_data(&fractal) == 1)
        return (1);
    if (check_fractal_type(argv[1], &fractal, argc, argv))
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