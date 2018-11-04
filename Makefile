NAME = avm
SRCNAME = main.cpp \
			parcer.cpp \
			lexer.cpp \
			Wrapper.cpp \
			IOperand.cpp \

SRC = $(addprefix src/, $(SRCNAME))

INC = -Iincludes

OBJ = $(SRC:.cpp=.o)
CFLAGS = -Wall -Wextra -Werror -std=c++11 -g
CC = g++
RM =	rm -f
ECHO	=	echo -e

%.o: %.cpp
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

all	:$(NAME)

$(NAME)	:$(OBJ)
	$(CC) $(OBJ) $(CFLAGSF) -o $(NAME)
	@$(ECHO) '\033[0;33m> Compiled\033[0m'

clean	:
	$(RM) $(OBJ)
	@$(ECHO) '\033[0;33m> Directory cleaned from obj\033[0m'

fclean	: clean
	$(RM) $(NAME)
	@$(ECHO) '\033[0;33m> Remove executable\033[0m'

re	: fclean all
