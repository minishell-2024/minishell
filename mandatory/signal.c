/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:19:10 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 18:35:00 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    signal_printf_off()
{
    struct termios  term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void    signal_printf_on()
{
    struct termios  term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void    print_empty_line(int sign)
{
    g_signal = sign;
    ft_putstr_fd("\n", STDERR_FILENO);
    exit(1);
}

void    print_empty_line_move_next(int sign) // 위 아래 차이를 잘 모르곘으
{
    g_signal = sign;
    ft_putstr_fd("\n", STDERR_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    // change_exit_code(line, 1);
}

void    set_normal_signal(t_line *line) // 일단적인 상태
{
    signal_printf_off(); // 표기 끄기
    signal(SIGINT,  print_empty_line);
    signal(SIGQUIT, SIG_IGN);
}

void    set_exec_signal(t_line *line)
{
    signal_print_on(); // 표시 키기
    signal(SIGINT, print_)
}

void    ignore_signal()
{
    signal(SIGINT, SIG_IGN); // ctrl + c
    signal(SIGQUIT, SIG_IGN); // ctrl + /
}


