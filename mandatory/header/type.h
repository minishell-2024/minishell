/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:29:50 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 19:51:40 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct s_env
{
	char			*key;
	char			*value;
	int				assignment;
	struct s_env	*env_next;
}	t_env;

typedef struct s_redirection
{
	int						fd;
	int						type;
	char					*file_name;
	char					*here_doc_eof;
	struct s_redirection	*redirect_next;
}	t_redirection;

typedef struct s_process
{
	char				**cmd;
	int					built_in_check;
	pid_t				pid;
	t_redirection		*redirect_node;
	struct s_process	*process_next;
}	t_process;

typedef struct s_line
{
	char		**argv;
	int			argc;
	int			std_fd[2];
	int			unset_path;
	t_env		*env;
	t_process	*proc;
}	t_line;

#endif
