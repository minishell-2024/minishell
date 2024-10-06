/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:28:39 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 19:40:59 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	change_exit_code(t_line *line, int return_val)
{
	t_env	*env;
	char	*exit_val;

	env = find_env(line, "?");
	if (!env)
		insert_env(line, "?", "0");
	exit_val = ft_itoa(return_val);
	if (!exit_val)
	{
		common_error("malloc", NULL, NULL, 1);
		delete_env(line, "?");
		insert_env(line, "?", "1");
		return ;
	}
	if (env->value)
		free(env->value);
	env->value = exit_val;
}

static void	check_process(t_line *line, int *status, int *sigint_check)
{
	t_process	*process;

	process = line->proc;
	while (process)
	{
		if (process->built_in_check == 0)
		{
			if (waitpid(process->pid, status, 0) == -1)
				common_error("waitpid", NULL, NULL, 0);
		}
		if (WIFSIGNALED(*status) && (*status & 127) == 2)
			*sigint_check = 1;
		process = process->process_next;
	}
}

void	wait_process(t_line *line)
{
	int			status;
	int			sigint_check;

	status = -100000000;
	sigint_check = 0;
	check_process(line, &status, &sigint_check);
	if (status == -100000000)
		return ;
	re_init_setting(line);
	if (sigint_check)
		ft_putstr_fd("\n", STDIN_FILENO);
	if (WIFSIGNALED(status))
	{
		if ((status & 127) == 3)
			ft_putstr_fd("Quit: 3\n", STDIN_FILENO);
		change_exit_code(line, status + 128);
	}
	else
		change_exit_code(line, WEXITSTATUS(status));
}

void	re_init_setting(t_line *line)
{
	close(STDIN_FILENO);
	if (dup2(line->std_fd[0], STDIN_FILENO) < 0)
		common_error("dup2", NULL, NULL, 0);
	close(STDOUT_FILENO);
	if (dup2(line->std_fd[1], STDOUT_FILENO) < 0)
		common_error("dup2", NULL, NULL, 0);
	set_normal_signal();
}

void	init_setting(t_line *line)
{
	line->std_fd[0] = dup(STDIN_FILENO);
	if (line->std_fd[0] < 0)
		common_error("dup", NULL, NULL, 0);
	line->std_fd[1] = dup(STDOUT_FILENO);
	if (line->std_fd[1] < 0)
		common_error("dup", NULL, NULL, 0);
	set_normal_signal();
}
