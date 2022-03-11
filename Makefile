NAME = philo
B_NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
B_SRCS = bonus/philo_bonus.c \
			bonus/parsing/check_in.c \
			bonus/allocation/allocation.c \
			bonus/threads/threads.c

			
M_SRCS = philo.c \
			check_in.c \
			allocation.c \
			threads.c
M_OBJS = $(M_SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

all : $(NAME)
bonus : $(B_NAME)

$(B_NAME) : $(B_OBJS) bonus/philo.h
	$(CC) $(CFLAGS) $(B_OBJS) -o $@

$(NAME) : $(M_OBJS) philo.h
	$(CC) $(CFLAGS) $(M_OBJS) -o $@
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(M_OBJS) $(B_OBJS)

fclean: clean
	rm -rf $(NAME) $(B_NAME)

re: fclean all
