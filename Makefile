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
TEST_E2E_SRC  = tests/e2e.cpp
TEST_E2E_OBJ  = tests/e2e.o

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
	-rm $(OBJS) $(MAIN_OBJ) $(TEST_UNIT_OBJ) $(TEST_E2E_OBJ)

fclean	: clean
	-rm $(NAME) $(TEST_MAIN_OBJ) tests/unit tests/e2e

re	: fclean all

run : all
	./$(NAME)

t	: all
	./$(NAME) tests/example.txt

rt	: fclean t

$(TEST_UNIT_OBJ) : $(TEST_UNIT_SRC)
	$(CC) $(CFLAGS) $(INCS_PATH) -c -o $@ $<

tests/unit	: $(OBJS) $(TEST_UNIT_OBJ)
	$(CC) $(CFLAGS) $(INCS_PATH) $(OBJS) $(TEST_UNIT_OBJ) -o $@

u	: tests/unit
	./$<

ru	: fclean u

$(TEST_E2E_OBJ) : $(TEST_E2E_SRC)
	$(CC) $(CFLAGS) $(INCS_PATH) -c -o $@ $<

tests/e2e: $(OBJS) $(TEST_E2E_OBJ)
	$(CC) $(CFLAGS) $(INCS_PATH) $(OBJS) $(TEST_E2E_OBJ) -o $@

e	: tests/e2e
	./$<

r2	: fclean e

test	: tests/unit $(NAME) tests/e2e
	$(LEAKS_CHECK) --leak-check=full ./tests/unit
	$(LEAKS_CHECK) ./tests/e2e

leaks : re
	$(LEAKS_CHECK) ./$(NAME)

.PHONY: clean fclean re run t rt u ru e r2 leaks

