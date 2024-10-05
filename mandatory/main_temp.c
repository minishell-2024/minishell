/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 13:44:43 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

void	main_loop(t_line *line, char *str);

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	line = create_line_node(argc, argv, envp);
	init_setting(line);
	while (1)
	{
		main_loop(line, str);
	}
	// rl_clear_history();
	// free_line(&line);
	// exit(errno);
}

void	main_loop(t_line *line, char *str)
{
	str = readline("minishell$ ");
	if (!str)
	{
		ft_putstr_fd("\033[1A", STDERR_FILENO); // 현재 커서의 위치를 한칸 위로 올려줌
		ft_putstr_fd("\033[11C", STDERR_FILENO); // 현재 커서의 위치를 12번째칸으로 이동
		ft_putendl_fd("exit", STDIN_FILENO);
		exit(0);
	}
	if (str[0])
		add_history(str);
	if (g_signal == SIGINT)
	{
		change_exit_code(line, 1);
		g_signal = 0;
	}
	if (process_line(str, line) == SUCCESS)
	{
		if (pipex(line, line->proc) && line->proc)
			wait_process(line);
	}
	free(str);
	free_process(&(line->proc));
	g_signal = 0;
	re_init_setting(line);
}
