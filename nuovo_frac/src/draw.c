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

static void draw_line(t_fractal *fractal, t_point p1, t_point p2)
{
    double delta_x;
    double delta_y;
    double pixel_x;
    double pixel_y;
    int steps;
    int i;

    delta_x = p2.x - p1.x;
    delta_y = p2.y - p1.y;
    steps = fmax(fabs(delta_x), fabs(delta_y));
    delta_x /= steps;
    delta_y /= steps;
    pixel_x = p1.x;
    pixel_y = p1.y;
    i = -1;
    while (++i <= steps)
    {
        my_mlx_pixel_put(fractal, (int)pixel_x, (int)pixel_y, 0xFFFFFF);
        pixel_x += delta_x;
        pixel_y += delta_y;
    }
}

static void sierpinski_recursive(t_fractal *fractal, t_point p1, 
    t_point p2, t_point p3, int depth)
{
    t_point mid1;
    t_point mid2;
    t_point mid3;

    if (depth == 0)
    {
        draw_line(fractal, p1, p2);
        draw_line(fractal, p2, p3);
        draw_line(fractal, p3, p1);
        return ;
    }
    mid1.x = (p1.x + p2.x) / 2;
    mid1.y = (p1.y + p2.y) / 2;
    mid2.x = (p2.x + p3.x) / 2;
    mid2.y = (p2.y + p3.y) / 2;
    mid3.x = (p3.x + p1.x) / 2;
    mid3.y = (p3.y + p1.y) / 2;
    sierpinski_recursive(fractal, p1, mid1, mid3, depth - 1);
    sierpinski_recursive(fractal, mid1, p2, mid2, depth - 1);
    sierpinski_recursive(fractal, mid3, mid2, p3, depth - 1);
}

void draw_sierpinski(t_fractal *fractal)
{
    t_point p1;
    t_point p2;
    t_point p3;
    int depth;

    mlx_clear_window(fractal->mlx, fractal->win);
    p1.x = WIDTH / 2;
    p1.y = 50;
    p2.x = 50;
    p2.y = HEIGHT - 50;
    p3.x = WIDTH - 50;
    p3.y = HEIGHT - 50;
    depth = 7;
    sierpinski_recursive(fractal, p1, p2, p3, depth);
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

static int iterate_lambda(t_complex z, int max_iter)
{
    t_complex c = {-1.0, 0.0};  // Parametro caratteristico del Lambda fractal
    int i;
    double temp;

    i = -1;
    while (++i < max_iter && complex_abs(z) <= 2.0)
    {
        temp = z.real * z.real - z.imag * z.imag;
        z.imag = 2 * z.real * z.imag;
        z.real = temp;
        z = complex_add(z, c);
    }
    return (i);
}

void draw_lambda(t_fractal *fractal)
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
            iterations = iterate_lambda(z, MAX_ITER);
            my_mlx_pixel_put(fractal, x, y, 
                create_psychedelic_color(iterations, MAX_ITER, fractal->color_shift));
        }
    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

static int iterate_celtic(t_complex c, int max_iter)
{
    t_complex z;
    double temp;
    int i;

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

void draw_celtic(t_fractal *fractal)
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
            iterations = iterate_celtic(c, MAX_ITER);
            my_mlx_pixel_put(fractal, x, y, 
                create_psychedelic_color(iterations, MAX_ITER, fractal->color_shift));
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
    else if (fractal->fractal_type == 6)
        draw_sierpinski(fractal);
    else if (fractal->fractal_type == 7)
        draw_lambda(fractal);
    else if (fractal->fractal_type == 8)
        draw_celtic(fractal);
}