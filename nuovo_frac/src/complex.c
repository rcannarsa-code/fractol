#include "../include/fractol.h"

t_complex complex_add(t_complex a, t_complex b)
{
    t_complex result;

    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return (result);
}

t_complex complex_multiply(t_complex a, t_complex b)
{
    t_complex result;

    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return (result);
}

double complex_abs(t_complex c)
{
    return (sqrt(c.real * c.real + c.imag * c.imag));
}

t_complex complex_divide(t_complex a, t_complex b)
{
    t_complex result;
    double denominator = b.real * b.real + b.imag * b.imag;
    result.real = (a.real * b.real + a.imag * b.imag) / denominator;
    result.imag = (a.imag * b.real - a.real * b.imag) / denominator;
    return (result);
}

t_complex get_scaled_coordinate(t_fractal *fractal, int x, int y)
{
    t_complex coord;
    coord.real = fractal->min_x + (x * (fractal->max_x - fractal->min_x)) 
        / WIDTH + fractal->move_x;
    coord.imag = fractal->min_y + (y * (fractal->max_y - fractal->min_y)) 
        / HEIGHT + fractal->move_y;
    return (coord);
}

t_complex complex_pow3(t_complex z)
{
    return complex_multiply(z, complex_multiply(z, z));
}