CC      = cc 
CFLAGS  = -Wall -Wextra -Werror -g3 -pthread
##-fsanitize=thread 
NAME    = philo

##SRC_DIR = src
##INCLUDE_DIRS = 

SOURCES = philo.c src/ft_atoi.c src/check_args.c src/free.c \
		  src/print.c src/init.c src/routine.c src/helper.c

OBJETS  = $(SOURCES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJETS)
	$(CC) $(CFLAGS) $(OBJETS) \
	-o $(NAME)


%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJETS)

good: all clean

fclean: clean
	rm -f $(NAME)

re: fclean all

