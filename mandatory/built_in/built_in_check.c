/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:37:20 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 19:37:45 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	do_built_in(t_line *line, t_process *process)
{
	int	return_val;

	return_val = 0;
	return_val = redirect_setting(process, 1);
	if (!return_val)
	{
		if (!ft_strncmp(process->cmd[0], "echo", 5))
			return_val = execute_echo(process);
		else if (!ft_strncmp(process->cmd[0], "cd", 3))
			return_val = execute_cd(line, process);
		else if (!ft_strncmp(process->cmd[0], "pwd", 4))
			return_val = execute_pwd();
		else if (!ft_strncmp(process->cmd[0], "export", 7))
			return_val = execute_export(line, process);
		else if (!ft_strncmp(process->cmd[0], "unset", 6))
			return_val = execute_unset(line, process);
		else if (!ft_strncmp(process->cmd[0], "env", 4))
			return_val = execute_env(line);
		else if (!ft_strncmp(process->cmd[0], "exit", 5))
			return_val = execute_exit(process);
	}
	change_exit_code(line, return_val);
	return (return_val);
}

int	check_built_in(t_process *process)
{
	if (!ft_strncmp(process->cmd[0], "echo", 5)
		|| !ft_strncmp(process->cmd[0], "cd", 3)
		|| !ft_strncmp(process->cmd[0], "pwd", 4)
		|| !ft_strncmp(process->cmd[0], "export", 7)
		|| !ft_strncmp(process->cmd[0], "unset", 6)
		|| !ft_strncmp(process->cmd[0], "env", 4)
		|| !ft_strncmp(process->cmd[0], "exit", 5))
		return (1);
	return (0);
}
