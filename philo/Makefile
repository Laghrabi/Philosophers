CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =  initialization.c  main.c	parsing.c
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