/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:25:56 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/17 20:33:59 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_line *line, t_process *process, int fd[2])
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(fd[1]);
	if (process->redirect_node) // redirection 없음
		redirect_setting(process);

	execute_command(line, process);
}

void	pipex(t_line *line, t_process *process)
{
	int	fd[2];

	while (process)
	{
		if (pipe(fd) < 0)
			common_error(NULL, "pipe", NULL, 0);
		process->pid = fork();
		if (process->pid < 0)
			common_error(NULL, "fork", NULL, 0);
		else if (process->pid == 0)
		{
			child_process(line, process, fd);
			exit(0);
		}
		else
		{
			close(fd[1]);
			if (dup2(fd[0], STDIN_FILENO) < 0)
				common_error(NULL, "dup2", NULL, 0);
			close(fd[0]);
			if (!process->process_next)
				close(STDIN_FILENO);
		}
		process = process->process_next;
	}
}
