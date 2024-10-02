NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
HEADERS = minishell.h typedef.h header/type.h
SRCS_DIR = mandatory
SRCS = main.c env.c lexer.c node.c parser.c process_line.c token.c

OBJS = $(SRCS:.c=.o)
HEADERS := $(addprefix $(SRCS_DIR)/, $(HEADERS))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

LIBRARY_DIR = libft
LIBRARY = $(LIBRARY_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C $(LIBRARY_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) $(LDFLAGS) -o $@

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	rm -f $(OBJS) $(LIBRARY)

fclean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	rm -f $(OBJS) $(LIBRARY) $(NAME)

re :
	@make fclean
	@make all

.PHONY: all clean fclean re
