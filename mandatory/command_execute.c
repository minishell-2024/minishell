/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:28:52 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/22 19:12:00 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"
#include "minishell.h"

void	execute_command(char *path, char **cmd, t_env *env)
{
	char	**env_var;

	env_var = make_env(env); // make_env 아직 미구현
	// strncmp 이거 길이 맞는지 체크 해보기.
	// if (!ft_strncmp(cmd[0], "minishell", 10))
	if (execve(path, cmd, env_var) < 0)
		common_error(cmd[0], NULL, NULL, 0);
}

void	check_execute(t_line *line, t_process *process)
{
	if (!ft_strncmp(process->cmd[0], "./", 2))
	{
		if (access(ft_strchr(process->cmd[0], "/") + 1, X_OK) < 0)
			common_error(process->cmd[0], NULL, NULL, 126);
		return (execute_command(process->cmd[0], process->cmd, line->env));
	}
	if (ft_strchr(process->cmd[0], '/') && access(process->cmd[0], X_OK) == 0)
		return (execute_command(process->cmd[0], process->cmd, line->env));
	return ;
}

char	**parse_path(t_env *env, int unset_path)
{
	int		i;
	int		index;
	char	**str;

	i = -1;
	index = -1;
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 5))
		{
			str = split_path(env->value, ':');
			if (!str)
				common_errror("malloc", NULL, NULL, 0);
			return (str);
		}
		env = env->env_next;
	}
	// 이부분 다시 한번 생각해보기.. path를 unset한 경우,,
	if (unset_path)
		return (0);
	str = split_path("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", ':');
	if (!str)
		common_errror("malloc", NULL, NULL, 0);
	return (str);
}

void	check_command(t_line *line, t_process *process)
{
	char	**path;
	char	*way;
	int		i;

	i = -1;
	check_execute(line, process);
	path = parse_path(line->env, line->unset_path);
	if (path)
	{
		while (path[++i])
		{
			way = ft_strjoin(path[i], process->cmd[0]);
			if (!way)
				common_error("malloc", NULL, NULL, 0);
			if (access(way, X_OK) == 0)
				execute_command(way, process->cmd, line->env);
			free(way);
		}
	}
	command_error(process->cmd[0]);
}
