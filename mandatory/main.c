/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 20:26:30 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	line = create_line_node(argc, argv, envp);
	init_setting(line);
	str = 0;
	while (1)
	{
		main_loop(line, str);
	}
	rl_clear_history();
	exit(errno);
}

void	main_loop(t_line *line, char *str)
{
	rl_catch_signals = 0;
	str = readline("minishell$ ");
	if (!str)
	{
		ft_putstr_fd("\033[1A", STDERR_FILENO);
		ft_putstr_fd("\033[11C", STDERR_FILENO);
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
		pipex(line, line->proc);
	free(str);
	free_process(&(line->proc));
	g_signal = 0;
	re_init_setting(line);
}
