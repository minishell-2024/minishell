/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:25:56 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/06 14:13:32 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	child_process(t_line *line, t_process *proc, int fd[2], int check)
{
	int	exit_val;

	exit_val = 0;
	set_origin_signal();
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(fd[1]);
	if (check)
	{
		if (dup2(line->std_fd[1], STDOUT_FILENO) < 0)
			common_error(NULL, "dup2", NULL, 0);
	}
	if (!proc->cmd)
		exit(redirect_setting(proc, 0));
	if (check_built_in(proc))
		exit(do_built_in(line, proc));
	if (proc->redirect_node)
		redirect_setting(proc, 0);
	check_command(line, proc);
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
