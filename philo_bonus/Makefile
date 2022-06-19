
NAME = philo_bonus

SRC =	philosophers.c philo_functions.c util_functions.c \
		initialize.c mutex.c launch.c file.c sem_functions.c

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

CFLAGS = -Wall -Wextra -Werror
AFLAGS = -g -O2 -fsanitize=thread

SRCDIR = ./src/
OBJDIR = ./obj/
INCDIR = ./inc/

HEADER = philosophers.h 

CC = cc

${OBJDIR}%.o : ${SRCDIR}%.c ${INCDIR}${HEADER}
	${CC} ${CFLAGS} -c $< -I${INCDIR} -o $@

all : ${NAME}

${NAME} : obj ${OBJ} 
	${CC} ${CFLAGS} -lpthread ${OBJ} -o $@ 

obj:
	mkdir -p $(OBJDIR)

clean :
	rm -f ${OBJ} $(addprefix $(OBJDIR), ${OBJ})
	
fclean : clean
	rm -f ${NAME}
		
re: fclean all

.PHONY: all clean fclean re
