/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:50:54 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 19:18:24 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	execute_echo(t_process *process)
{
	int	check;
	int	i;

	i = 1;
	redirect_setting(process);
	if (!process->cmd[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (!ft_strncmp(process->cmd[i], "-n", 3))
	{
		i++;
		check = 1;
	}
	else
		check = 0;
	while (process->cmd[i])
	{
		if (!process->cmd[i + 1] && check == 1) // -n 옵션에 다음 문장이 없다면
			ft_putstr_fd(process->cmd[i], STDOUT_FILENO);
		else
			ft_putendl_fd(process->cmd[i], STDOUT_FILENO);
	}
	return (0);
}
