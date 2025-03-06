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

TEST_MAIN_SRC	= tests/main.cpp
TEST_MAIN_OBJ	= tests/main.o

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
	-rm $(OBJS) $(MAIN_OBJ) 

fclean	: clean
	-rm $(NAME) $(TEST_MAIN_OBJ) tests/unit

re	: fclean all

run : all
	./$(NAME)

t	: all
	./$(NAME) tests/example.txt

$(TEST_MAIN_OBJ) : $(TEST_MAIN_SRC)
	$(CC) $(CFLAGS) $(INCS_PATH) -c -o $@ $<

tests/unit	: $(OBJS) $(TEST_MAIN_OBJ)
	$(CC) $(CFLAGS) $(INCS_PATH) $(OBJS) $(TEST_MAIN_OBJ) -o tests/unit

u	: tests/unit
	./tests/unit

ru	: fclean u

rt	: fclean t

leaks : re
	$(LEAKS_CHECK) ./$(NAME)

.PHONY: all clean fclean re run t rt leaks

