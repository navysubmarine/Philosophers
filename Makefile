CC      = cc 
CFLAGS  = -Wall -Wextra -Werror -g3 -pthread -fsanitize=thread,undefined 
NAME    = philo

##SRC_DIR = src
##INCLUDE_DIRS = 

SOURCES = philo.c ft_atoi.c check_args.c free.c \
		  print.c init_struct.c init_threads.c helper.c \
		  actions.c routine_philo.c routine_supervisor.c init_mutex.c

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

