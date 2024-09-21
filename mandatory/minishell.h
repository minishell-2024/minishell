/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:12:52 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/21 22:00:35 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
// # include <unistd.h>
// # include <stddef.h>
// # include <stdlib.h>

# include <stdio.h>
// printf
# include <readline/readline.h>
// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <fcntl.h>
// open
# include <sys/wait.h>
// wait, waitpid, wait3, wait4
# include <signal.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>
// stat, lstat, fstat
# include <dirent.h>
// opendir, readdir, closedir
# include <string.h>
// strerror
# include <sys/ioctl.h>
// ioctl
# include <termios.h>
// tcsetattr, tcgerattr
# include <term.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// flag value definition
# define FAIL 0
# define SUCCESS 1
# define QUOTE_INCOMPLETE 2

// global variable
int	g_signal;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef	enum e_tokentype
{
	TOKEN_END,
	TOKEN_COMMAND,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_DLESS,
	TOKEN_DGREAT
}	t_tokentype;

typedef struct s_command
{
	char	*line;
	char	**path;
	char	**command;
	char	**env;
	int		flag;
	pid_t	*pid;
	// char	**pipe;
	// char	**cc;
	// char 	**filename;
	
}	t_command;

typedef struct s_parsed
{

}	t_parsed;

typedef struct s_token
{
	char			*word;
	t_tokentype		token_type;
	struct s_token	*next;
}	t_token;

int		parsing(char *line, t_env *envp);
int		check_quote(char *line);
int		tokenize(char *line, t_token *tokens);
char	*read_string(char *line);
char	*read_word(char *line);
int		add_token(t_token **token_addr, char *str);
t_tokentype	get_tokentype(char *str);
void	replace_env(t_token *token, t_env *envp);
char	*insert_env(char *origin, char *val, int name_size);

#endif
