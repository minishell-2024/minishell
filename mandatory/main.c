/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 16:00:07 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		error_occur("malloc", NULL, NULL, 1);
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

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	// 초기 parse
	// $?를 env에 추가...
	std_fd_dup(line); // 기존 표준 입출력 복사.
	while (1)
	{
		str = readline("minishell$ ");
		// printf("%s\n", str);

		// parseing
		if (str && str[0])
			add_history(str);
		pipex(line, line->proc);
		wait_process(line);
		free_all(line); // 미완, 할당한거 다 free.. 아마 line->proc 부터만 처리하면? 될듯?
		free(str);
		fd_setting(line); // 기존 표준 입력, 출력으로 되돌리기..
	}
	rl_clear_history();
	exit(errno);
}
