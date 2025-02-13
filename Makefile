NAME	= avm

CC		= clang++ #g++
CFLAGS	= -Wall -Wextra
CFLAGS	+= -Werror
CFLAGS	+= -std=c++14 #-pedantic

ifdef DEBUG
CFLAGS	+= -g3 -fsanitize=address
else
ifdef DEBUGL
CFLAGS += -g3
endif
endif

LEAKS_CHECK = valgrind

FILES	= main Int8 Int16 Int32 Float Double Factory

OBJS_PATH = objs/
SRCS_PATH = srcs/
INCS_PATH = -Iincludes/.

SRCS	= $(addprefix $(SRCS_PATH), $(addsuffix .cpp, $(FILES)))
OBJS	= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))

all	: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $(INCS_PATH) -o $@ $<

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean	:
	-rm $(OBJS)

fclean	: clean
	-rm $(NAME)

re	: fclean all

run : all
	./$(NAME)

t	: all
	./$(NAME) tests/example.txt

leaks : re
	$(LEAKS_CHECK) ./$(NAME)

.PHONY: all clean fclean re run t leaks

