NAME = avm

SRC_FILES = \
			src/main.cpp     \
			src/Factory.cpp  \

OBJ_FILES = \
			obj/main.o      \
			obj/Factory.o   \

CC = g++
C_FLAGS = -Wall -Werror -Wextra -fsanitize=address

all: $(NAME)

obj/%.o : src/%.cpp
	@mkdir -p obj
	$(CC) $(C_FLAGS) -Iincludes/ -c $< -o $@

$(NAME) : $(OBJ_FILES)
	$(CC) $(C_FLAGS) -Iincludes/ $< -o $(NAME)

t : $(NAME)
	./$(NAME) tests/example.txt

i : $(NAME)
	./$(NAME)

clean :
	-rm -r obj

fclean : clean
	-rm $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re t i

