NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c \
       src/check_arguments.c \
       src/clean_simulation.c \
       src/init_mutexes.c \
       src/init_philos.c \
       src/init_simulation.c \
       src/print_actions.c \
       src/routine_management.c \
       src/thread_management.c \
       src/utils1.c \
       src/utils2.c
	   
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
