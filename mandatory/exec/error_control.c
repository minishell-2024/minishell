/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:00:50 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 19:18:24 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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


void	command_error(char *str)
{
	const char	*error_msg = "command not found";

	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
	exit(127);
}

int	error_occur(char *cmd, char *file_name, char *custom_msg, int error_code)
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
		return (error_code);
	return (errno);
}
