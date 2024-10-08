/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:24:30 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 18:55:41 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	execute_unset(t_line *line, t_process *process)
{
	int		i;

	i = 0;
	if (!process->cmd[1])
		return (0);
	while (process->cmd[++i])
	{
		if (!is_identifier(process->cmd[i]))
			return (error_occur("unset", NULL, "not a valid identifier", 1));
		if (find_env(line, process->cmd[i]))
			delete_env(line, process->cmd[i]);
	}
	return (0);
}
