NAME	= avm

CC		= g++
CFLAGS	= -Wall -Wextra
CFLAGS	+= -Werror
CFLAGS	+= -std=c++17 #-pedantic

ifdef DEBUG
CFLAGS	+= -g3 -fsanitize=address
else
ifdef DEBUGL
CFLAGS += -g3
endif
endif

LEAKS_CHECK = valgrind

FILES	= Factory Stack Lexer Token SyntaxError Parser Runtime Instruction IOperand

MAIN_SRC	= srcs/main.cpp
MAIN_OBJ	= objs/main.o

TEST_UNIT_SRC = tests/unit.cpp
TEST_UNIT_OBJ = tests/unit.o

OBJS_PATH = objs/
SRCS_PATH = srcs/
INCS_PATH = -Iincludes/.

SRCS	= $(addprefix $(SRCS_PATH), $(addsuffix .cpp, $(FILES)))
OBJS	= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))

all	: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $(INCS_PATH) -o $@ $<

$(NAME)	: $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) -o $@

clean	:
	-rm $(OBJS) $(MAIN_OBJ) $(TEST_UNIT_OBJ)

fclean	: clean
	-rm $(NAME) $(TEST_MAIN_OBJ) tests/unit tests/e2e

re	: fclean all

run : all
	./$(NAME)

$(TEST_UNIT_OBJ) : $(TEST_UNIT_SRC)
	$(CC) $(CFLAGS) $(INCS_PATH) -c -o $@ $<

tests/unit	: $(OBJS) $(TEST_UNIT_OBJ)
	$(CC) $(CFLAGS) $(INCS_PATH) $(OBJS) $(TEST_UNIT_OBJ) -o $@

u	: tests/unit
	./$<

ru	: fclean u

e	: $(NAME)
	cd tests && ./e2e.sh

test	: $(NAME) tests/unit 
	$(LEAKS_CHECK) --leak-check=full ./tests/unit
	cd tests && ./e2e.sh

leaks : re
	$(LEAKS_CHECK) ./$(NAME)

.PHONY: clean fclean re run u ru e test leaks

