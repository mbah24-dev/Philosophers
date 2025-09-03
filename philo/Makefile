# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 00:03:00 by mbah              #+#    #+#              #
#    Updated: 2025/04/07 15:42:08 by mbah             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      ?= philo
CC         = cc
DIR        = src
APP        = app
UTILITY    = utility
CORE       = core
INC        = inc
CFLAGS     = -Wall -Werror -Wextra -I $(INC)
HEADER     = $(INC)/philosophers.h 
SRC        = $(DIR)/$(APP)/$(CORE)/initializer.c $(DIR)/$(APP)/$(UTILITY)/external_func.c \
			 $(DIR)/$(APP)/$(UTILITY)/philo_utils.c $(DIR)/$(APP)/$(CORE)/check_arguments.c \
			 $(DIR)/$(APP)/$(CORE)/dining_simulation.c $(DIR)/main.c

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
