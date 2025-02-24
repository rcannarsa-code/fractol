/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:24:33 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 13:56:18 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

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

	t = (double)iterations / max_iter;
	if (iterations == max_iter)
		return (0xFFFFFF);
	if (iterations < 10)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else
	{
		r = sin(0.3 * t * 20 + color_shift) * 127 + 128;
		g = sin(0.3 * t * 20 + 2 + color_shift) * 127 + 128;
		b = sin(0.3 * t * 20 + 4 + color_shift) * 127 + 128;
	}
	return (create_trgb(0, r, g, b));
}

/* int create_psychedelic_color(int iterations, int max_iter, int color_shift)
{
    double t = (double)iterations / max_iter;
    int r, g, b;
    
    // Se il punto è nel set,
	ritorna bianco per creare contrasto col background nero
    if (iterations == max_iter)
        return (0xFFFFFF);

    // Crea colori psichedelici con shift
    r = sin(0.3 * t * 20 + color_shift) * 127 + 128;
    g = sin(0.3 * t * 20 + 2 + color_shift) * 127 + 128;
    b = sin(0.3 * t * 20 + 4 + color_shift) * 127 + 128;

    return (create_trgb(0, r, g, b));
} */