/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:25:56 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 18:38:55 by yuyu             ###   ########.fr       */
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
	if (!ft_strncmp(process->cmd[0], "echo", 5) || !ft_strncmp(process->cmd[0], "cd", 3)
		|| !ft_strncmp(process->cmd[0], "pwd", 4) || !ft_strncmp(process->cmd[0], "export", 7)
		||	!ft_strncmp(process->cmd[0], "unset", 6) || !ft_strncmp(process->cmd[0], "env", 4)
		||	!ft_strncmp(process->cmd[0], "exit", 5))
		return (1);
	return (0);
}

static void	child_process(t_line *line, t_process *process, int fd[2], int check_last)
{
	int	exit_val;

	exit_val = 0;
	set_origin_signal();
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(fd[1]);
	// 마지막 process라면, 표준 out으로 해야함. (stdout에 있는거 닫아버리고)
	if (check_last)
	{
		if (dup2(line->std_fd[1], STDOUT_FILENO) < 0)
			common_error(NULL, "dup2", NULL, 0);
	}
	if (!process->cmd)
		exit(redirect_setting(process, 0));
	if (check_built_in(process))
		exit(do_built_in(line, process));
	if (process->redirect_node) // redirection 있음
		redirect_setting(process, 0);
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

int	multi_pipex(t_line *line, t_process *process)
{
	int	fd[2];
	int	check_last_process;

	check_last_process = 0;
	while (process)
	{
		if (!process->process_next)
			check_last_process = 1;
		if (pipe(fd) < 0)
			common_error(NULL, "pipe", NULL, 0);
		process->pid = fork();
		if (process->pid < 0)
			common_error(NULL, "fork", NULL, 0);
		else if (process->pid == 0)
			child_process(line, process, fd, check_last_process);
		else
			parent_process(process, fd);
		process = process->process_next;
	}
	return (1);
}

void	pipex(t_line *line, t_process *process)
{
	if (!heredoc_setting(line, process))
		return ;
	if (!process->process_next && !process->cmd)
	{
		change_exit_code(line, redirect_setting(process, 1));
		return ;
	}
	else if (!process->process_next && check_built_in(process))
		do_built_in(line, process);
	else
	{
		if (multi_pipex(line, process))
			wait_process(line);
	}
}
