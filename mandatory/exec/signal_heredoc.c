/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:23:08 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 18:37:49 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void    print_empty_line(int sign)
{
    g_signal = sign;
    ft_putstr_fd("\n", STDIN_FILENO);
    exit(1);
}

void    do_heredoc_sigint(int sign)
{
    (void) sign;
    g_signal = 1;
    write(STDOUT_FILENO, "\n", 1);
    close(0);
}

void    set_heredoc_signal()
{
    signal(SIGINT, do_heredoc_sigint);
    signal(SIGQUIT, SIG_IGN);
}

void    heredoc_ctrl_d()
{
    ft_putstr_fd("\033[1A", STDERR_FILENO); // 현재 커서의 위치를 한칸 위로 올려줌
    ft_putstr_fd("\033[2C", STDERR_FILENO); // 현재 커서의 위치를 12번째칸으로 이동
}
