CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
SRCS =  initialization.c  main.c	parsing.c	utils.c	philo.c	monitor.c
OBJS = $(SRCS:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)


fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY: $(OBJS) $(SRCS)