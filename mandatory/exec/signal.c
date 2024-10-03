// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   signal.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/29 18:19:10 by yuyu              #+#    #+#             */
// /*   Updated: 2024/10/02 19:18:24 by jihyjeon         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../header/minishell.h"

static void    signal_printf_switch(int sign)
{
    struct termios  term;

    tcgetattr(STDIN_FILENO, &term);
	if (sign) // on
		term.c_lflag |= ~(ECHOCTL);
	else // off
    	term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void    print_empty_line_move_next(int sign) // 위 아래 차이를 잘 모르곘으
{
    g_signal = sign;
    ft_putstr_fd("\n", STDERR_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    set_normal_signal() // 일단적인 프롬프트
{
    signal_printf_switch(0); // 표기 끄기
    signal(SIGINT,  print_empty_line_move_next);
    signal(SIGQUIT, SIG_IGN);
}

void    ignore_signal()
{
    signal(SIGINT, SIG_IGN); // ctrl + c
    signal(SIGQUIT, SIG_IGN); // ctrl + /
}

void	set_origin_signal(void)
{
    signal_printf_switch(1); // on
	signal(SIGINT, SIG_DFL); // ctrl+c 시그널 입력시 동작을 기본 시그널 설정으로 되돌림
	signal(SIGQUIT, SIG_DFL); // ctrl+\ 시그널 입력시 동작을 기본 시그널 설정으로 되돌림
}
