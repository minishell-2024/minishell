/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:12:52 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/22 03:40:02 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "typedef.h"
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

int		parsing(char *line);
int		check_quote(char *line);
int		tokenize(char *line, t_token *tokens);
char	*read_string(char *line);
char	*read_word(char *line);
int		add_token(t_token **token_addr, char *str);
t_tokentype	get_tokentype(char *str);

#endif
