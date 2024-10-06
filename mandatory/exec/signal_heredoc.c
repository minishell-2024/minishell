/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:23:08 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 20:26:10 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	print_empty_line(int sign)
{
	g_signal = sign;
	ft_putstr_fd("\n", STDIN_FILENO);
	exit(1);
}

void	do_heredoc_sigint(int sign)
{
	(void) sign;
	g_signal = 1;
	close(0);
}

void	set_heredoc_signal(void)
{
	signal(SIGINT, do_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_ctrl_d(void)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putstr_fd("\033[2C", STDERR_FILENO);
}
