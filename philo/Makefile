# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:36:25 by ilchahbi          #+#    #+#              #
#    Updated: 2024/10/04 14:47:49 by ilchahbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = philo

SRCS = threads_rot.c parsing.c philo_utils.c philosophers.c free_fun.c lst_utils.c
	
OBJCTS = $(SRCS:%.c=%.o)

$(NAME) : $(OBJCTS) philosophers.h
		$(CC) $(CFLAGS)  $(OBJCTS) -o $(NAME) 
			
all: $(NAME)
	
clean:	
				rm -f $(OBJCTS)

fclean: clean
				rm -f $(NAME)

re: fclean all  