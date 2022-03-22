# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 09:58:55 by arohmann          #+#    #+#              #
#    Updated: 2022/03/17 22:25:50 by annarohmnn       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_B = philo_bonus

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -g

OBJDIR = obj

SRC = main.c utils.c utils2.c init.c action.c

SRC_B = 

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
OBJ_B = $(SRC_B:%.c=$(OBJDIR)/%.o) 

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@



.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)
	
$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_B) -o $(NAME_B)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_B)

re: fclean all

bonus: $(NAME_B)
