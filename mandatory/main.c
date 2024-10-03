/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/03 14:27:34 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	// 초기 parse
	// $?를 env에 추가...
	line = (t_line *)ft_calloc(sizeof(t_line), 1);
	if (!line)
		common_error("malloc", NULL, NULL, 1);
	make_env(line, envp);
	line->argc = argc;
	line->argv = argv;
	init_setting(line); // 기존 표준 입출력 복사.
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			ft_putendl_fd("exit", STDIN_FILENO);
			exit(0);
		}
		add_history(str);
		parse(str, line);
		// printf("%s\n", str);

		// parseing
		if (str && str[0])
			add_history(str);
		pipex(line, line->proc);
		wait_process(line);
		// free_all(line); // 미완, 할당한거 다 free.. 아마 line->proc 부터만 처리하면? 될듯?
		free(str);
		re_init_setting(line); // fd, singal 되돌리기
	}
	rl_clear_history();
	exit(errno);
}
