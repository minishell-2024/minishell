/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:25:56 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/29 13:28:31 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built_in(t_line *line, t_process *process)
{
	int	reuturn_val;
	redirect_setting(process);
	if (ft_strncmp(process->cmd[0], "echo", 5))
		return (execute_echo(process));
	else if (ft_strncmp(process->cmd[0], "cd", 3))
		return (execute_cd(line, process));
	else if (ft_strncmp(process->cmd[0], "pwd", 4))
		return (execute_pwd(process));
	else if (ft_strncmp(process->cmd[0], "export", 7))
		//
	else if (ft_strncmp(process->cmd[0], "unset", 6))
		return (execute_unset(line, process));
	else if (ft_strncmp(process->cmd[0], "env", 4))
		return (execute_env(line, process));
	else if (ft_strncmp(process->cmd[0], "exit", 5))
		//
	else
		return (-1);
	//  built_in 미완 $? 때문에
}

void	child_process(t_line *line, t_process *process, int fd[2])
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(fd[1]);
	if (process->redirect_node) // redirection 있음
		redirect_setting(process);

	check_command(line, process);
	exit(errno);
}

void	pipex(t_line *line, t_process *process)
{
	int	fd[2];

	while (process)
	{
		if (check_bulit_in(line, process) == -1) // $? 처리때문에, 25줄 넘쳐서 쪼개야할듯. + ?값 저장할 공간 필요 t_line *line에 추가하면 될듯..!
		{
			if (pipe(fd) < 0)
				common_error(NULL, "pipe", NULL, 0);
			process->pid = fork();
			if (process->pid < 0)
				common_error(NULL, "fork", NULL, 0);
			else if (process->pid == 0)
				child_process(line, process, fd);
			else
			{
				close(fd[1]);
				if (dup2(fd[0], STDIN_FILENO) < 0)
					common_error(NULL, "dup2", NULL, 0);
				close(fd[0]);
				if (!process->process_next)
					close(STDIN_FILENO);
			}
		}
		process = process->process_next;
	}
}
