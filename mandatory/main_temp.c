/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 12:27:11 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	// std_fd_dup(line); // 기존 표준 입출력 복사.
	line = create_line_node(argc, argv, envp);
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		if (process_line(str, line) == SUCCESS)
			;//parse 성공
		else
			;//parse 실패 (FAIL OR QUOTE INCOMPLETE)
		free(str);
		free_process(&(line->proc));
	}
	// rl_clear_history();
	free_line(&line);
	exit(errno);
}

