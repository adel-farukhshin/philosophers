
NAME = philosophers

SRC =	philosophers.c 

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

CFLAGS = -Wall -Wextra -Werror -pthread

D_FILES = ${patsubst %.c,%.d,${SRC}}

LIBDIR = "../ft_printf"
LIB = "ftprintf"

SRCDIR = ./src/
OBJDIR = ./obj/
INCDIR = ./inc/
#BONUSDIR = ./bonus/

HEADER = philosophers.h

${OBJDIR}%.o : ${SRCDIR}%.c
	cc ${CFLAGS} -c $< -I${INCDIR} -o $@ -MMD


all : ${NAME}

${NAME} : obj ${OBJ} 
	${CC} ${LDFLAGS} ${OBJ} -o $@ 

obj:
	mkdir -p $(OBJDIR)

include ${wildcard ${D_FILES}}

clean :
	rm -f ${OBJ} $(addprefix $(OBJDIR),$(D_FILES))
	
fclean : clean
	rm -f ${NAME}
		
re: fclean all

.PHONY: all clean fclean re bonus
