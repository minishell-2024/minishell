NAME = minishell

CC = cc
CFLAG = -Wall -Wextra -Werror -lreadline
HEADERS = minishell.h
SRCS_DIR = mandatory
SRCS = main.c	\


OBJS = $(SRCS:.c=.o)
HEADERS := $(addprefix $(SRCS_DIR)/, $(HEADERS))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

LIBRARY_DIR = libft
LIBRARY = $(LIBRARY_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C $(LIBRARY_DIR)
	$(CC) $(CFLAG) $(OBJS) $(LIBRARY) -o $@

# $(MANDATORY_NAME) : $(OBJS)
# 	@$(MAKE) -C $(LIBRARY_DIR)
# 	$(CC) $(CFLAG) $(OBJS) $(LIBRARY) -o $@
# 	cp $(MANDATORY_NAME) $(NAME)
# 	@rm -rf $(BONUS_NAME)

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# bonus : $(BONUS_NAME)

# $(BONUS_NAME) : $(BONUS_OBJS)
# 	@$(MAKE) -C $(LIBRARY_DIR)
# 	$(CC) $(CFLAG) $(BONUS_OBJS) $(LIBRARY) -o $@
# 	cp $(BONUS_NAME) $(NAME)
# 	@rm -rf $(MANDATORY_NAME)

# $(BONUS_DIR)%.o : $(BONUS_DIR)%.c $(BONUS_HEADERS)
# 	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	rm -rf $(OBJS) $(LIBRARY)

fclean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	rm -rf $(OBJS) $(LIBRARY) $(NAME)

re :
	@make fclean
	@make all
