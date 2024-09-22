/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:12:52 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/21 20:19:37 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "type.h"
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
# include <errno.h>
# include <string.h>
// strerror
# include <sys/ioctl.h>
// ioctl
# include <termios.h>
// tcsetattr, tcgerattr
# include <term.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// global variable
int	singal;


//==================== error_control.c ====================
void	common_error(char *cmd, char *file_name, char *custom_msg, int error_code);
void	command_error(char *str);
int		error_occur(char *cmd, char *file_name, char *custom_msg, int error_code);

//==================== pipex.c ====================
void	pipex(t_line *line, t_process *process);

//==================== redirect.c ====================
void	redirect_setting(t_process *process);

//==================== split_path.c ====================
char	**split_path(char const *s, char c);

//==================== command_execute.c ====================
void	execute_command(char *path, char **cmd, t_env *env);
void	check_execute(t_line *line, t_process *process);
char	**parse_path(t_env *env, int unset_path);
void	check_command(t_line *line, t_process *process);

#endif
