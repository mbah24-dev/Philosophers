# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 00:03:00 by mbah              #+#    #+#              #
#    Updated: 2025/09/17 18:13:57 by mbah             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME      ?= philo
CC         = cc
DIR        = src/app
APP        = app
UTILITY    = utility
CORE       = core
INC        = inc
CFLAGS     = -Wall -Werror -Wextra -fsanitize=address -g -I $(INC)
HEADER     = $(INC)/philosophers.h
SRC        = src/main.c $(DIR)/cleanup.c $(DIR)/monitor.c $(DIR)/init.c \
			$(DIR)/status.c $(DIR)/parsing.c $(DIR)/philosopher_routine.c \
			$(DIR)/time.c
OBJDIR     = obj
OBJS       = $(SRC:.c=.o)
OBJF       = $(addprefix $(OBJDIR)/, $(notdir $(OBJS)))

$(NAME): $(OBJF)
	$(CC) $(CFLAGS) $(OBJF) -o $(NAME)

$(OBJDIR)/%.o: src/%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/app/%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
