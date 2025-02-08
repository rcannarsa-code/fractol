#include "../include/fractol.h"

void my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
{
    char *dst;

    dst = fractal->addr + (y * fractal->line_length + x * (fractal->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int create_psychedelic_color(int iterations, int max_iter, int color_shift)
{
    double t = (double)iterations / max_iter;
    int r, g, b;
    
    // Se il punto è nel set, ritorna bianco per creare contrasto col background nero
    if (iterations == max_iter)
        return (0xFFFFFF);

    // Crea colori psichedelici con shift
    r = sin(0.3 * t * 20 + color_shift) * 127 + 128;
    g = sin(0.3 * t * 20 + 2 + color_shift) * 127 + 128;
    b = sin(0.3 * t * 20 + 4 + color_shift) * 127 + 128;

    return (create_trgb(0, r, g, b));
}

int iterate_mandelbrot(t_complex c, int max_iter)
{
    t_complex z;
    int i;

    z.real = 0;
    z.imag = 0;
    i = -1;
    while (++i < max_iter && complex_abs(z) <= 2.0)
        z = complex_add(complex_multiply(z, z), c);
    return (i);
}

void draw_mandelbrot(t_fractal *fractal)
{
    int x;
    int y;
    t_complex c;
    int iterations;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            c = get_scaled_coordinate(fractal, x, y);
            iterations = iterate_mandelbrot(c, MAX_ITER);
            my_mlx_pixel_put(fractal, x, y, 
                create_psychedelic_color(iterations, MAX_ITER, fractal->color_shift));
        }
    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

int iterate_julia(t_complex z, t_complex c, int max_iter)
{
    int i;

    i = -1;
    while (++i < max_iter && complex_abs(z) <= 2.0)
        z = complex_add(complex_multiply(z, z), c);
    return (i);
}

void draw_julia(t_fractal *fractal)
{
    int x;
    int y;
    t_complex z;
    int iterations;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            z = get_scaled_coordinate(fractal, x, y);
            iterations = iterate_julia(z, fractal->julia_c, MAX_ITER);
            my_mlx_pixel_put(fractal, x, y, 
                create_psychedelic_color(iterations, MAX_ITER, fractal->color_shift));
        }
    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

int iterate_burning_ship(t_complex c, int max_iter)
{
    t_complex z;
    double temp;
    int i;

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

void draw_burning_ship(t_fractal *fractal)
{
    int x;
    int y;
    t_complex c;
    int iterations;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            c = get_scaled_coordinate(fractal, x, y);
            iterations = iterate_burning_ship(c, MAX_ITER);
            my_mlx_pixel_put(fractal, x, y, 
                create_psychedelic_color(iterations, MAX_ITER, fractal->color_shift));
        }
    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

int iterate_tricorn(t_complex c, int max_iter)
{
    t_complex z;
    double temp;
    int i;

    z.real = 0;
    z.imag = 0;
    i = -1;
    while (++i < max_iter && complex_abs(z) <= 2.0)
    {
        temp = z.real;
        z.real = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = -2.0 * temp * z.imag + c.imag;
    }
    return (i);
}

void draw_tricorn(t_fractal *fractal)
{
    int x;
    int y;
    t_complex c;
    int iterations;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            c = get_scaled_coordinate(fractal, x, y);
            iterations = iterate_tricorn(c, MAX_ITER);
            my_mlx_pixel_put(fractal, x, y, 
                create_psychedelic_color(iterations, MAX_ITER, fractal->color_shift));
        }
    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

static t_complex find_closest_root(t_complex z)
{
    const t_complex roots[3] = {
        {1, 0},
        {-0.5, 0.866025},
        {-0.5, -0.866025}
    };
    double min_dist;
    int closest;
    int i;

    min_dist = INFINITY;
    closest = 0;
    i = -1;
    while (++i < 3)
    {
        double dist = sqrt(pow(z.real - roots[i].real, 2) + 
            pow(z.imag - roots[i].imag, 2));
        if (dist < min_dist)
        {
            min_dist = dist;
            closest = i;
        }
    }
    return (roots[closest]);
}

static int get_root_color(t_complex z, int iterations)
{
    t_complex closest;
    
    closest = find_closest_root(z);
    if (closest.real > 0)
        return (create_trgb(0, 255 - iterations * 2, iterations * 2, iterations * 2));
    else if (closest.imag > 0)
        return (create_trgb(0, iterations * 2, 255 - iterations * 2, iterations * 2));
    return (create_trgb(0, iterations * 2, iterations * 2, 255 - iterations * 2));
}

static int iterate_newton(t_complex *z, int max_iter)
{
    int i;
    const double tolerance = 1e-6;
    t_complex z_new;

    i = 0;
    while (i < max_iter)
    {
        t_complex z3 = complex_pow3(*z);
        t_complex z2 = complex_multiply(*z, *z);
        t_complex num = complex_add(z3, (t_complex){-1, 0});
        t_complex den = (t_complex){3 * z2.real, 3 * z2.imag};
        t_complex frac = complex_divide(num, den);
        z_new = complex_add(*z, (t_complex){-frac.real, -frac.imag});
        
        if (sqrt(pow(z_new.real - z->real, 2) + 
            pow(z_new.imag - z->imag, 2)) < tolerance)
            break;
        *z = z_new;
        i++;
    }
    return (i);
}

void draw_newton(t_fractal *fractal)
{
    int x;
    int y;
    t_complex z;
    int iterations;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            z = get_scaled_coordinate(fractal, x, y);
            iterations = iterate_newton(&z, MAX_ITER);
            if (iterations == MAX_ITER)
                my_mlx_pixel_put(fractal, x, y, 0x000000);
            else
                my_mlx_pixel_put(fractal, x, y, get_root_color(z, iterations));
        }
    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

void draw_fractal(t_fractal *fractal)
{
    if (fractal->fractal_type == 1)
        draw_mandelbrot(fractal);
    else if (fractal->fractal_type == 2)
        draw_julia(fractal);
    else if (fractal->fractal_type == 3)
        draw_burning_ship(fractal);
    else if (fractal->fractal_type == 4)
        draw_newton(fractal);
    else if (fractal->fractal_type == 5)
        draw_tricorn(fractal);
}