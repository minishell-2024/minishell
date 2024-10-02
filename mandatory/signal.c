/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:19:10 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/29 18:21:50 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    set_signal()
{
    struct termios  term;
    // 표기 끄기
    signal(SIGINT, 빈문자열_handle);
    singal(SIGQOIT, SIG_IGN);    
}

void    ignore_signal()
{
    signal(SIGINT, SIG_IGN); // ctrl + c
    signal(SIGQUIT, SIG_IGN); // ctrl + /
}