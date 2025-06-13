SRCS = clean.c ft_atoi.c init.c philoroutine.c\
       main.c monitoring.c philos.c\

OBJS = $(SRCS:.c=.o)
NAME = philo
CFLAGS = -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo/philo.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
