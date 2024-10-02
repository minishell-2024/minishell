/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 20:28:21 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	t_line	*line;
	char	*str;

	// 초기 parse
	// $?를 env에 추가...
	std_fd_dup(line); // 기존 표준 입출력 복사.
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		parse(str, line);
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
