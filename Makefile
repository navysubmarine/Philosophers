CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3
NAME    = so_long

SRC_DIR = src
INCLUDE_DIRS = -Iincludes -Ift_printf/includes -Ilibft/includes -Imlx_linux/minilibx-linux

SOURCES = main.c \
          get_next_line.c check_map1.c \
		  check_map2.c check_map3.c  check_map4.c \
          map_utils.c init_map.c exit.c \
          move.c render.c init_game.c load_sprites.c

OBJETS  = $(SOURCES:.c=.o)

FTPRINTF = ft_printf/libftprintf.a
LIBFT    = libft/libft.a

MLX_DIR = mlx_linux/minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext -lm -lz

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJETS) $(FTPRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJETS) \
	-Llibft -lft \
	-Lft_printf -lftprintf \
	$(MLX_LIB) \
	-o $(NAME)


%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@


$(FTPRINTF):
	@$(MAKE) -C ft_printf

$(LIBFT):
	@$(MAKE) -C libft


clean:
	@$(MAKE) clean -C ft_printf
	@$(MAKE) clean -C libft
	rm -f $(OBJETS)

good: all clean

fclean: clean
	@$(MAKE) fclean -C ft_printf
	@$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

