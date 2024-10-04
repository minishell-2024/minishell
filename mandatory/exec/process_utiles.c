/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:28:39 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/04 18:12:47 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	change_exit_code(t_line *line, int return_val)
{
	t_env	*env;
	char	*exit_val;

	env = find_env(line, "?");
	if (!env) // 이럴리가 없어야 하긴 함.
		insert_env(line, "?", "0");
	exit_val = ft_itoa(return_val);
	if (!exit_val) // 처리가 좀 애매하긴 함..
	{
		common_error("malloc", NULL, NULL, 1);
		delete_env(line, "?"); // 실패 처리해야하나...
		insert_env(line, "?", "1");
		return ;
	}
	if (env->value)
		free(env->value);
	env->value = exit_val;
}

void	wait_process(t_line *line)
{
	t_process	*process;
	int			status;

	process = line->proc;
	status = -100000000;
	while (process)
	{
		if (process->built_in_check == 0)
		{
			if (waitpid(process->pid, &status, 0) == -1)
				common_error("waitpid", NULL, NULL, 0);
		}
		process = process->process_next;
	}
	if (status == -100000000)
		return ;
	if (WIFSIGNALED(status))
	{
		if ((status & 127) == 3)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		change_exit_code(line, status + 128); // child_process가 비정상적으로 종료.. deadlock같은걸로 종료되면 실행되는 듯?
	}
	else
		change_exit_code(line, WEXITSTATUS(status));
}

void    re_init_setting(t_line *line)
{
	// printf("%d %d %d %d", STDIN_FILENO, STDOUT_FILENO, line->std_fd[0], line->std_fd[1]);
    close(STDIN_FILENO);
	if (dup2(line->std_fd[0], STDIN_FILENO) < 0)
		common_error("dup2", NULL, NULL, 0);
	close(STDOUT_FILENO);
	if (dup2(line->std_fd[1], STDOUT_FILENO) < 0)
		common_error("dup2", NULL, NULL, 0);
    set_normal_signal();
}

void    init_setting(t_line *line)
{
	line->std_fd[0] = dup(STDIN_FILENO);
	if (line->std_fd[0] < 0)
		common_error("dup", NULL, NULL, 0);
	line->std_fd[1] = dup(STDOUT_FILENO);
	if (line->std_fd[1] < 0)
		common_error("dup", NULL, NULL, 0);
	// printf("%d %d\n", line->std_fd[0], line->std_fd[1]);
	set_normal_signal();
}
