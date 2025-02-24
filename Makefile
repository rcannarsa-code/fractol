NAME = fractol

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBFTDIR = libft
MLXDIR = minilibx-linux

# Source files
SRC = main.c init.c hooks.c draw.c complex.c handle.c iterate.c color.c
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L$(MLXDIR) -lmlx -L/usr/lib -lXext -lX11 -lm
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/includes -I$(MLXDIR)

# LibFT
LIBFT = $(LIBFTDIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFTDIR)/includes

# Colors for pretty printing
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

all: $(NAME)

# Create necessary directories
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compile libft
$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(NC)"
	@make -C $(LIBFTDIR)
	@echo "$(GREEN)Libft compiled successfully!$(NC)"

# Compile MLX
$(MLXDIR)/libmlx.a:
	@echo "$(YELLOW)Compiling MinilibX...$(NC)"
	@make -C $(MLXDIR)
	@echo "$(GREEN)MinilibX compiled successfully!$(NC)"

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link everything together
$(NAME): $(LIBFT) $(MLXDIR)/libmlx.a $(OBJS)
	@echo "$(YELLOW)Linking fractol...$(NC)"
	@$(CC) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)Fractol compiled successfully!$(NC)"

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean
	@make -C $(MLXDIR) clean

fclean: clean
	@echo "$(RED)Cleaning everything...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re