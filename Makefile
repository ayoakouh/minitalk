# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 02:54:07 by ayoakouh          #+#    #+#              #
#    Updated: 2025/03/10 23:40:24 by ayoakouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = M/client.c M/server.c minitalk_utils.c
OBJS = $(SRCS:.c=.o)
CLIENT_NAME = client
SERVER_NAME = server

BONUS_SRCS = bonus/client_bonus.c bonus/server_bonus.c bonus/minitalk_bonus_utils.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
CLIENT_BONUS_NAME = client_bonus
SERVER_BONUS_NAME = server_bonus

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): M/client.o M/minitalk_utils.o
	$(CC) $(CFLAGS) M/client.o M/minitalk_utils.o -o $(CLIENT_NAME)

$(SERVER_NAME): M/server.o M/minitalk_utils.o
	$(CC) $(CFLAGS) M/server.o M/minitalk_utils.o -o $(SERVER_NAME)

$(OBJS): M/minitalk.h

bonus: $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

$(CLIENT_BONUS_NAME): bonus/client_bonus.o bonus/minitalk_bonus_utils.o bonus/ft_atoi.o
	$(CC) $(CFLAGS) bonus/client_bonus.o bonus/minitalk_bonus_utils.o bonus/ft_atoi.o -o $(CLIENT_BONUS_NAME)

$(SERVER_BONUS_NAME): bonus/server_bonus.o bonus/minitalk_bonus_utils.o bonus/ft_atoi.o
	$(CC) $(CFLAGS) bonus/server_bonus.o bonus/minitalk_bonus_utils.o bonus/ft_atoi.o -o $(SERVER_BONUS_NAME)

$(BONUS_OBJS): bonus/minitalk_bonus.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re