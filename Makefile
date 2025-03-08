# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 02:54:07 by ayoakouh          #+#    #+#              #
#    Updated: 2025/03/08 03:38:08 by ayoakouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME = client
SERVER_NAME = server
SERVER_BONUS_NAME = server_bonus
CLIENT_BONUS_NAME = client_bonus
CLIENT_SRC = client.c
SERVER_SRC = server.c
CLIENT_BONUS_SRC = client_bonus.c minitalk_bonus_utils.c
SERVER_BONUS_SRC = server_bonus.c minitalk_bonus_utils.c
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INCLUDE = minitalk.h
INCLUDE_BONUS = minitalk_bonus.h
CC = cc
OBJ_S = ${SERVER_SRC:.c=.o}
OBJ_C = ${CLIENT_SRC:.c=.o}
OBJ_BONUS_C = ${CLIENT_BONUS_SRC:.c=.o}
OBJ_BONUS_S = ${SERVER_BONUS_SRC:.c=.o}

all: $(SERVER_NAME) $(CLIENT_NAME)

bonus: $(SERVER_BONUS_NAME) $(CLIENT_BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_NAME): $(OBJ_S)
	$(CC) $(CFLAGS) $(OBJ_S) -o $(SERVER_NAME)

$(CLIENT_NAME): $(OBJ_C)
	$(CC) $(CFLAGS) $(OBJ_C) -o $(CLIENT_NAME)

$(SERVER_BONUS_NAME): $(OBJ_BONUS_S)
	$(CC) $(CFLAGS) $(OBJ_BONUS_S) -o $(SERVER_BONUS_NAME)

$(CLIENT_BONUS_NAME): $(OBJ_BONUS_C)
	$(CC) $(CFLAGS) $(OBJ_BONUS_C) -o $(CLIENT_BONUS_NAME)

clean:
	$(RM) $(OBJ_C) $(OBJ_S) $(OBJ_BONUS_C) $(OBJ_BONUS_S)

fclean: clean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re