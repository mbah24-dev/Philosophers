# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 00:03:00 by mbah              #+#    #+#              #
#    Updated: 2025/03/06 00:03:01 by mbah             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      ?= philosophers
CC         = cc
DIR        = src
INC        = inc
CFLAGS     = -Wall -Werror -Wextra -I $(INC)
HEADER     = $(INC)/philosophers.h 
SRC        = $(DIR)/main.c 

OBJS       = $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
	
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
