/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:28:52 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 01:02:06 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_command(char *path, char **cmd, t_env *env)
{
	char	**env_var;
	int		index;

	env_var = make_envp(env); // make_env 아직 미구현b
	// if (env_var) // 이거 환경변수 없을 떄 실행될수 있어서 한번 더 생각해보기
	// 	common_error("malloc", NULL, NULL, 0);
	// int index = -1;
	// while (env_var[++index])
	// 	ft_putendl_fd(env_var[index], 2);
	if (execve(path, cmd, env_var) < 0)
	{	// if (env_var)가 위에 주석처리 헤제시라고 가정했으.
		index = -1;
		while(env_var[++index])
			free(env_var);
		free(env_var);
		common_error(cmd[0], NULL, NULL, 0);
	}
}

void	check_execute(t_line *line, t_process *process)
{
	if (!ft_strncmp(process->cmd[0], "./", 2))
	{
		if (access(ft_strchr(process->cmd[0], '/') + 1, X_OK) < 0)
			common_error(process->cmd[0], NULL, NULL, 126);
		return (execute_command(process->cmd[0], process->cmd, line->env));
	}
	if (ft_strchr(process->cmd[0], '/') && access(process->cmd[0], X_OK) == 0)
		return (execute_command(process->cmd[0], process->cmd, line->env));
	return ;
}

char	**parse_path(t_env *env)
{
//	int		i;
//	int		index;
	char	**str;

//	i = -1;
//	index = -1;
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 5))
		{
			str = split_path(env->value, ':');
			if (!str)
				common_error("malloc", NULL, NULL, 0);
			return (str);
		}
		env = env->env_next;
	}
	return (0);
}

void	check_command(t_line *line, t_process *process)
{
	char	**path;
	char	*way;
	int		i;

	i = -1;
	check_execute(line, process);
	path = parse_path(line->env);
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
