/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:00:50 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/08 22:08:29 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	common_error(char *cmd, char *file_name, char *custom_msg, int error_code)
{
	const char	*error_msg = strerror(errno);

	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(": ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (file_name)
	{
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (custom_msg)
		ft_putendl_fd(custom_msg, 2);
	else
		ft_putendl_fd(error_msg, 2);
	if (error_code)
		exit(error_code);
	exit(errno);
}


void	command_error(t_process *process, char *str)
{
	const char	*error_msg = "command not found";

	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
	exit(127);
}

void	error_occur(char *s)
{
	const char	*str = strerror(errno);

	if (s)
		ft_putstr_fd(s, 2);
	if (errno != 0)
		ft_putstr_fd(str, 2);
	exit(errno);
}
