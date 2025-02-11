NAME = avm

SRC_FILES = \
			src/main.cpp

OBJ_FILES = \
			obj/main.o

CC = clang
C_FLAGS = -Wall -Werror -Wextra

all: $(NAME)

obj/%.o : src/%.cpp
	@mkdir -p obj
	$(CC) $(C_FLAGS) -Iincludes/ -c $< -o $@

$(NAME) : $(OBJ_FILES)
	$(CC) $(C_FLAGS) -Iincludes $< -o $(NAME)

clean :
	-rm -r obj

fclean : clean
	-rm $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re

