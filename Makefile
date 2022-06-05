
NAME = philo

SRC =	philosophers.c philo_functions.c util_functions.c initialize.c launch.c

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

CFLAGS = -Wall -Wextra -Werror 
EFLAGS = -fsanitize=thread

D_FILES = ${patsubst %.c,%.d,${SRC}}

LIBDIR = "../ft_printf"
LIB = "ftprintf"

SRCDIR = ./src/
OBJDIR = ./obj/
INCDIR = ./inc/
#BONUSDIR = ./bonus/q

HEADER = philosophers.h

${OBJDIR}%.o : ${SRCDIR}%.c
	gcc ${CFLAGS} -c $< -I${INCDIR} -o $@ -MMD


all : ${NAME}

${NAME} : obj ${OBJ} 
	${CC} ${CFLAGS} -lpthread ${OBJ} -o $@ 

obj:
	mkdir -p $(OBJDIR)

include ${wildcard ${D_FILES}}

clean :
	rm -f ${OBJ} $(addprefix $(OBJDIR),$(D_FILES))
	
fclean : clean
	rm -f ${NAME}
		
re: fclean all

.PHONY: all clean fclean re bonus
