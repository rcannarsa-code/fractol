NAME = fractol

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBFTDIR = libft
MLXDIR = minilibx-linux

# Source files
SRC = main.c init.c hooks.c draw.c complex.c handle.c iterate.c color.c params.c
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L$(MLXDIR) -lmlx -L/usr/lib -lXext -lX11 -lm
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/includes -I$(MLXDIR)

# LibFT
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

$(MLXDIR)/libmlx.a:
	make -C $(MLXDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(MLXDIR)/libmlx.a $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(LIBFTDIR) clean
	make -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re