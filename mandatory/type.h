/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:29:50 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/08 21:28:15 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# ifndef UNISTD_H
#  include <unistd.h>
# endif

# define PROGRAM_NAME "minishell"

// 환경변수
typedef struct s_env
{
	char	*str;
	t_env	*env_next;
}	t_env;

// redirection
typedef struct s_redirection
{
	int				fd;
	int				type; // < << > >> ...
	char			*file_name;
	t_redirection	*redirect_next;
}	t_redirection;

// typedef struct s_command
// {
// 	char		*cmd;
// 	t_command	*cmd_next;
// }	t_command;

// process
typedef struct s_process
{
	// t_command		*cmd_node;
	char			**cmd;
	int				built_in_check;
	pid_t			*pid;
	t_redirection	*redirect_node;
	t_process		*process_next; // process_next != 0  ==> '|' exist
}	t_process;


typedef struct s_line
{
	char		**argv;
	char		*argc;
	t_env		*env;
	t_process	*proc;
}	t_line;

#endif
