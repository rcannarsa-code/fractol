NAME = libft.a
INCLUDES_DIR := includes
LIBFT_DIR := src/libft_src
PRINTF_DIR := src/ft_printf_src
GNL_DIR := src/get_next_line_src

LIBFT_SRC = srcs/libft_src/ft_isalpha.c srcs/libft_src/ft_isdigit.c srcs/libft_src/ft_isalnum.c srcs/libft_src/ft_isascii.c srcs/libft_src/ft_isprint.c \
    srcs/libft_src/ft_strlen.c srcs/libft_src/ft_memset.c srcs/libft_src/ft_bzero.c srcs/libft_src/ft_memcpy.c srcs/libft_src/ft_memmove.c \
    srcs/libft_src/ft_strlcpy.c srcs/libft_src/ft_strlcat.c srcs/libft_src/ft_toupper.c srcs/libft_src/ft_tolower.c srcs/libft_src/ft_strchr.c \
    srcs/libft_src/ft_strrchr.c srcs/libft_src/ft_strncmp.c srcs/libft_src/ft_memchr.c srcs/libft_src/ft_memcmp.c srcs/libft_src/ft_strnstr.c \
    srcs/libft_src/ft_atoi.c srcs/libft_src/ft_calloc.c srcs/libft_src/ft_strdup.c srcs/libft_src/ft_substr.c srcs/libft_src/ft_strjoin.c \
    srcs/libft_src/ft_strtrim.c srcs/libft_src/ft_split.c srcs/libft_src/ft_itoa.c srcs/libft_src/ft_strmapi.c srcs/libft_src/ft_striteri.c \
    srcs/libft_src/ft_putchar_fd.c srcs/libft_src/ft_putstr_fd.c srcs/libft_src/ft_putendl_fd.c srcs/libft_src/ft_putnbr_fd.c \
	srcs/libft_src/ft_lstnew.c srcs/libft_src/ft_lstadd_front.c srcs/libft_src/ft_lstsize.c srcs/libft_src/ft_lstlast.c \
	srcs/libft_src/ft_lstadd_back.c srcs/libft_src/ft_lstdelone.c srcs/libft_src/ft_lstclear.c srcs/libft_src/ft_lstiter.c srcs/libft_src/ft_lstmap.c
PRINTF_SRC = srcs/ft_printf_src/ft_printf.c srcs/ft_printf_src/ft_printf_utils.c srcs/ft_printf_src/ft_print_hex.c srcs/ft_printf_src/ft_print_ptr.c srcs/ft_printf_src/ft_print_unsigned.c
GNL_SRC = srcs/get_next_line_src/get_next_line.c srcs/get_next_line_src/get_next_line_utils.c srcs/get_next_line_src/get_next_line_bonus.c srcs/get_next_line_src/get_next_line_utils_bonus.c

OBJECTS = $(LIBFT_SRC:.c=.o) $(PRINTF_SRC:.c=.o) $(GNL_SRC:.c=.o)


CC = cc
AR = ar rcs
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
IFLAG = -I $(INCLUDES_DIR)

$(NAME): $(OBJECTS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAG) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re