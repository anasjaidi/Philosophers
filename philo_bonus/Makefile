NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
			
M_SRCS = philo.c \
			check_in.c \
			allocation.c \
			threads.c
M_OBJS = $(M_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(M_OBJS) philo.h
	$(CC) $(CFLAGS) $(M_OBJS) -o $@
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(M_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
