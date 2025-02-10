#include "../include/fractol.h"

int handle_close(t_fractal *fractal)
{
    cleanup_data(fractal);
    exit(0);
    return (0);
}

void move_view(int keycode, t_fractal *fractal)
{
    double move_step;

    move_step = 0.1 * fractal->zoom;
    if (keycode == KEY_LEFT)
        fractal->move_x -= move_step;
    else if (keycode == KEY_RIGHT)
        fractal->move_x += move_step;
    else if (keycode == KEY_UP)
        fractal->move_y -= move_step;
    else if (keycode == KEY_DOWN)
        fractal->move_y += move_step;
}

void shift_colors(t_fractal *fractal)
{
    fractal->color_shift += 1;
    if (fractal->color_shift > 360)
        fractal->color_shift = 0;
}

int handle_keypress(int keycode, t_fractal *fractal)
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

void update_zoom(t_fractal *fractal, double zoom_factor, double x_before, double y_before)
{
    double new_width;
    double new_height;

    new_width = (fractal->max_x - fractal->min_x) * zoom_factor;
    new_height = (fractal->max_y - fractal->min_y) * zoom_factor;
    fractal->min_x = x_before - (x_before - fractal->min_x) * zoom_factor;
    fractal->max_x = fractal->min_x + new_width;
    fractal->min_y = y_before - (y_before - fractal->min_y) * zoom_factor;
    fractal->max_y = fractal->min_y + new_height;
}

int handle_mouse(int button, int x, int y, t_fractal *fractal)
{
    double x_before_zoom;
    double y_before_zoom;
    double zoom_factor;
    double width;

    x_before_zoom = fractal->min_x + (x * (fractal->max_x - fractal->min_x)) / WIDTH;
    y_before_zoom = fractal->min_y + (y * (fractal->max_y - fractal->min_y)) / HEIGHT;
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
    fractal->max_iter = (int)(MAX_ITER_BASE * (1 + 2 * log10(1/width)));
    if (fractal->max_iter < MAX_ITER_BASE)
        fractal->max_iter = MAX_ITER_BASE;
    draw_fractal(fractal);
    return (0);
}

void setup_hooks(t_fractal *fractal)
{
    mlx_hook(fractal->win, 2, 1L<<0, handle_keypress, fractal);
    mlx_hook(fractal->win, 17, 0, handle_close, fractal);
    mlx_mouse_hook(fractal->win, handle_mouse, fractal);
}