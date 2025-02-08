#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER_BASE 100
# define MAX_ITER fractal->max_iter

// Keyboard keys
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_C 99
# define KEY_ESC 65307

typedef struct s_complex
{
    double real;
    double imag;
} t_complex;

typedef struct s_fractal
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    double min_x;
    double max_x;
    double min_y;
    double max_y;
    int max_iter;
    int fractal_type;  // 1: Mandelbrot, 2: Julia, 3: Burning Ship
    t_complex julia_c;
    double zoom;
    double move_x;
    double move_y;
    int color_shift;
} t_fractal;

// Prototipi delle funzioni
int init_data(t_fractal *fractal);
void cleanup_data(t_fractal *fractal);
int handle_keypress(int keycode, t_fractal *fractal);
int handle_mouse(int button, int x, int y, t_fractal *fractal);
int handle_close(t_fractal *fractal);
void setup_hooks(t_fractal *fractal);
void draw_mandelbrot(t_fractal *fractal);
void draw_julia(t_fractal *fractal);
void draw_burning_ship(t_fractal *fractal);
void draw_newton(t_fractal *fractal);
void draw_tricorn(t_fractal *fractal);
void my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color);
int create_trgb(int t, int r, int g, int b);
t_complex complex_add(t_complex a, t_complex b);
t_complex complex_multiply(t_complex a, t_complex b);
t_complex complex_divide(t_complex a, t_complex b);
t_complex complex_pow3(t_complex z);
t_complex get_scaled_coordinate(t_fractal *fractal, int x, int y);
double complex_abs(t_complex c);
void move_view(int keycode, t_fractal *fractal);
void shift_colors(t_fractal *fractal);
void draw_fractal(t_fractal *fractal);

#endif