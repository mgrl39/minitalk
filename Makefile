# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 19:37:08 by meghribe          #+#    #+#              #
#    Updated: 2025/01/11 23:18:33 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f

SRC = client.c server.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): server client

server: Makefile minitalk.h utils.o server.o
	$(CC) $(FLAGS) utils.o server.o -o server

client: Makefile minitalk.h utils.o client.o
	$(CC) $(FLAGS) utils.o client.o -o client

clean:
	$(RM) $(OBJ)

%.o: %.c Makefile minitalk.h
	$(CC) $(FLAGS) -c $< -o $@ 

fclean: clean
	$(RM) client server

re: fclean all

.PHONY: all clean fclean re
