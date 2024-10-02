/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:28:39 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 20:32:05 by yuyu             ###   ########.fr       */
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
	if (env->key)
		free(env->key);
	env->key = exit_val;
}

void	wait_process(t_line *line)
{
	// 미완
	t_process	*process;
	int			status;

	process = line->proc;
	while (process)
	{
		if (process->built_in_check == 0)
		{
			if (waitpid(process->pid, &status, 0) == -1)
				common_error("waitpid", NULL, NULL, 0);
		}
		process = process->process_next;
	}
	if (WIFEXITED(status))
		change_exit_code(line, WEXITSTATUS(status));
	else
		change_exit_code(line, EXIT_FAILURE); // child_process가 비정상적으로 종료.. deadlock같은걸로 종료되면 실행되는 듯?
	// minishell에서는 위에가 맞을 듯.
	// if (WIFEXITED(status))
	// 	exit(WEXITSTATUS(status));
	// else
	// 	exit(EXIT_FAILURE);
}

void	std_fd_dup(t_line *line)
{
	if (dup2(STDIN_FILENO, line->std_fd[0]) < 0)
		common_error("dup2", NULL, NULL, 0);
	if (dup2(STDOUT_FILENO, line->std_fd[1]) < 0)
		common_error("dup2", NULL, NULL, 0);
}

void	fd_setting(t_line *line)
{
	if (dup2(line->std_fd[0], STDIN_FILENO) < 0)
		common_error("dup2", NULL, NULL, 0);
	if (dup2(line->std_fd[1], STDOUT_FILENO) < 0)
		common_error("dup2", NULL, NULL, 0);
}
