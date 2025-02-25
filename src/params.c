/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:39:16 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/25 18:41:22 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void parse_julia_params(t_fractal *fractal, int argc, char **argv)
{
    if (argc >= 3)
        fractal->julia_c.real = ft_atof(argv[2]);
    if (argc >= 4)
        fractal->julia_c.imag = ft_atof(argv[3]);
}

void set_julia_params(t_fractal *fractal)
{
    fractal->fractal_type = JULIA;
    fractal->julia_c.real = -0.7;
    fractal->julia_c.imag = 0.27015;
}