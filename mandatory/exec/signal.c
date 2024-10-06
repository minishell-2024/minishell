/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:45:25 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 19:55:17 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	signal_printf_switch(int sign)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (sign)
		term.c_lflag |= (ECHOCTL);
	else
		term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	print_empty_line_move_next(int sign)
{
	g_signal = sign;
	ft_putstr_fd("\n", STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_normal_signal(void)
{
	signal_printf_switch(0);
	signal(SIGINT, print_empty_line_move_next);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_origin_signal(void)
{
	signal_printf_switch(1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
