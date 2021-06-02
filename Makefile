NAME = gnl
CC = clang
CFLAGS = -Wall -Werror -Wextra -g -D BUFFER_SIZE=$(BUFFER_SIZE)
RM = rm -f

BUFFER_SIZE = 12

SRCS = get_next_line.c get_next_line_utils.c
OBJECTS := $(SRCS:.c=.o)
INCLUDES = -I.

DEBUGGER = valgrind
DEBUGFLAGS = -q --leak-check=full --show-leak-kinds=all -s --track-origins=yes --show-error-list=yes

DEBUGDIR = tests

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ main.c -o $@

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

debug: re
	@echo -e "\e[38;5;42m[BUFFER_SIZE = $(BUFFER_SIZE)]\e[0m"
	@for file in `find $(DEBUGDIR) -type f`; do \
		echo -e "\e[38;5;38mFILE: $$file\e[0m"; \
		$(DEBUGGER) $(DEBUGFLAGS) ./$(NAME) "$$file" 1>/dev/null; \
	done

.PHONY: all clean fclean re debug
