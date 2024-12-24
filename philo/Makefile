# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 11:13:24 by dakojic           #+#    #+#              #
#    Updated: 2024/05/27 10:19:49 by dakojic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

FLAGS = -Wall -Werror -Wextra -g3 -pthread -lpthread ##-fsanitize=thread

CC = cc
RM = rm -rf

SRC = philo.c utils.c setter.c diner.c life.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
		$(CC) $(FLAGS)  -o $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

