NAME	= xorstrings

CC	= gcc

CXXFLAGS += -Wall -Wextra -Werror
CXXFLAGS += -I./include/

SRCDIR = ./src/
OBJDIR = ./obj/

SRC=	$(SRCDIR)xorstring.c	\
	$(SRCDIR)options.c \
	$(SRCDIR)xor.c

OBJ= $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
