/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:29:50 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/29 18:56:21 by yuyu             ###   ########.fr       */
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
	char	*key;
	char	*value;
	int		assignment; // = 여부 해야하나...
	t_env	*env_next;
}	t_env;

// redirection
typedef struct s_redirection
{
	int				fd;
	int				type; // < << > >> ...
	char			*file_name;
	char			*here_doc_eof; // 종료조건 << asdf 라면 "asdf"
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
	int				built_in_check; // 1 : built_in // 0 : not built_in
	pid_t			*pid;
	t_redirection	*redirect_node;
	t_process		*process_next; // process_next != 0  ==> '|' exist
}	t_process;


typedef struct s_line
{
	char		**argv;
	char		*argc;
	int			unset_path; // unset PATH를 했으면, path 자동추가 취소 -> 1 // 만약 환경변수 추가할 때, PATH= 이 나오면 다시 0으로 초기화 필요..
	t_env		*env;
	t_process	*proc;
}	t_line;

#endif
