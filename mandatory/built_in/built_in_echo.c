/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:50:54 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/22 21:23:47 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"
#include "minishell.h"

int	execute_echo(t_process *process)
{
	int	check;
	int	i;

	i = 1;
	if (!process->cmd[1])
	{
		write(STDIN_FILENO, "\n", 1);
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
			ft_putstr_fd(process->cmd[i], STDIN_FILENO);
		else
			ft_putendl_fd(process->cmd[i], STDIN_FILENO);
	}
	return (0);
}
