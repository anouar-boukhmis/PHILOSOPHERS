# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 21:09:27 by aboukhmi          #+#    #+#              #
#    Updated: 2025/07/04 20:10:50 by aboukhmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi_bonus.c init_bonus.c philo_bonus.c\
       monitoring_bonus.c routine_bonus.c utils_bonus.c\

OBJS = $(SRCS:.c=.o)
NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo_bonus.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
