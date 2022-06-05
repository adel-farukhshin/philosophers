# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchristi <lchristi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 13:31:09 by lchristi          #+#    #+#              #
#    Updated: 2022/06/01 13:31:12 by lchristi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAG1 = -fsanitize=thread
FLAG2 = -pthread
HEADER = ./inc/philo_bonus.h

SRCS =	./src/philo_bonus.c\
		./src/check.c\
		./src/debug.c\
		./src/lunch.c\
		./src/time.c\
		./src/utils.c\

OBJ = $(patsubst %.c, %.o, $(SRCS))

RED= \033[4;31m
GREEN= \033[0;32m
NC= \033[0;0m

.PHONY:	all clean fclean re norm

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(FLAG2) $(OBJ) -o $(NAME)
			@echo -e "$(GREEN)\t\n Philo compiled! \n $(NC)"

%.o : %.c 	Makefile $(HEADER)
			$(CC) $(FLAGS) -c $< -o $@

clean:
			rm -f $(OBJ)
			@echo -e "$(RED)*.o files is clean!$(NC)"

fclean:		clean
			rm -f $(NAME)
			@echo -e "$(RED)All files is clean!$(NC)"

re:			fclean all

norm:
			@norminette $(HEADER) $(SRCS)
