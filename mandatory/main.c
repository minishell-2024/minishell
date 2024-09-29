/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/29 19:10:18 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	// 초기 parse
	// $?를 env에 추가...
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
	}
	rl_clear_history();
	exit(errno);
}
