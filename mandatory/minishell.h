/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:12:52 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 12:45:32 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "typedef.h"
# include "header/type.h"
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

# include <stdio.h>
// printf
# include <readline/readline.h>
# include <readline/history.h>
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
int				g_signal;

//process_line (parse main)
int				parse(char *line, t_line *input);
int				check_quote(char *line);
int				tokenize(char *line, t_token **tokens);
t_process		*lexer(t_token *tokens, t_env *env);
int				add_token(t_token **token, char *s, t_tokentype type, int flag);
//tokenize
t_state			handle_general(t_token **t, char **b, char **p, int *s);
t_state			handle_quote(t_state state, char c, char **buf_ptr);
char			*append_char(char *buf, char c);
char			*get_redirect(char **ptr);
char			*reset_buf(int *sq_flag);
//lexer
void			key_to_value(t_token *token, t_env *envp);
char			*insert_value(char *origin, char *val, int name_size);
//parser
t_process		*parse_pipe(t_token **ptr);
char			**parse_command(t_token **ptr, t_redirection **redirect);
void			append_redir(t_redirection **head, t_token **ptr, int type);
char			**append_simple_cmd(char **cmd, t_token **ptr);
//node (util)
t_token			*create_token_node(t_tokentype type, int sq_flag);
t_process		*create_process_node(void);
t_redirection	*create_redir_node(int redir_type);
t_env			*create_env_node(char *key, char *value);
int				which_redir(char *word);
//env
int				make_env(t_line *line, char **envp);
char			**make_envp(t_env *env);
int				insert_env(t_line *line, char *key, char *value);
int				change_env_value(t_line *line, char *key, char *new_value);

#endif
