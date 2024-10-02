/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:25:56 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 19:41:47 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_built_in(t_line *line, t_process *process)
{
	int	return_val;

	if (ft_strncmp(process->cmd[0], "echo", 5))
		return_val = execute_echo(process);
	else if (ft_strncmp(process->cmd[0], "cd", 3))
		return_val = execute_cd(line, process);
	else if (ft_strncmp(process->cmd[0], "pwd", 4))
		return_val = execute_pwd(process);
	else if (ft_strncmp(process->cmd[0], "export", 7))
		return_val = execute_export(line, process);
	else if (ft_strncmp(process->cmd[0], "unset", 6))
		return_val = execute_unset(line, process);
	else if (ft_strncmp(process->cmd[0], "env", 4))
		return_val = execute_env(line, process);
	else if (ft_strncmp(process->cmd[0], "exit", 5))
		return_val = execute_exit(line, process);
	else
		return (0);
	process->built_in_check = 1;
	// $? 처리
	change_exit_code(line, return_val);
	return (1);
}

static void	child_process(t_line *line, t_process *process, int fd[2])
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

static void	parent_process(t_process *process, int fd[2])
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(fd[0]);
	if (!process->process_next)
		close(STDIN_FILENO);
}

void	pipex(t_line *line, t_process *process)
{
	int	fd[2];

	while (process)
	{
		heredoc_setting(process);
		if (check_built_in(line, process) == 0) // $? 처리때문에, 25줄 넘쳐서 쪼개야할듯. + ?값 저장할 공간 필요 t_line *line에 추가하면 될듯..!
		{
			if (pipe(fd) < 0)
				common_error(NULL, "pipe", NULL, 0);
			process->pid = fork();
			if (process->pid < 0)
				common_error(NULL, "fork", NULL, 0);
			else if (process->pid == 0)
				child_process(line, process, fd);
			else
				parent_process(process, fd);
		}
		process = process->process_next;
	}
}
