# .DEFAULT_GOAL := all
NAME		= minishell

CC			= cc
CFLAGS		= -MMD -MP -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS		= -lreadline
SRCS_DIR	= mandatory
SRC			= main.c
PARSE_SRCS	= env.c lexer.c node.c parser.c process_line.c token.c env_tool.c memory_manage.c token_tool.c
EXEC_SRCS	= process_utiles.c command_execute.c env_utiles.c error_control.c \
			heredoc_setting.c pipex.c redirect.c signal.c signal_heredoc.c split_path.c
BUILTIN_SRCS= built_in_cd.c built_in_echo.c built_in_exit.c built_in_export.c \
			built_in_pwd.c built_in_unset.c built_in_utiles.c built_in_env.c built_in_check.c

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRC)) \
			$(addprefix $(SRCS_DIR)/parsing/, $(PARSE_SRCS)) \
			$(addprefix $(SRCS_DIR)/exec/, $(EXEC_SRCS)) \
			$(addprefix $(SRCS_DIR)/built_in/, $(BUILTIN_SRCS)) \


OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)

INCLUDES	= -Iheader
LIBRARY_DIR = libft
LIBRARY 	= $(LIBRARY_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C $(LIBRARY_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) $(LDFLAGS) -o $@
	@echo "$(NAME): object file and $(NAME) created"

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	@rm -f $(OBJS) $(LIBRARY) $(DEPS)
	@echo "$(NAME): objects deleted"

fclean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	@rm -f $(OBJS) $(LIBRARY) $(DEPS) $(NAME)
	@echo "$(NAME): $(NAME) deleted"


re :
	make fclean
	make all

.PHONY: all clean fclean re
