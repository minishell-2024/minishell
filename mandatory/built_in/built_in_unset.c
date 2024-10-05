/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:24:30 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 15:53:03 by yuyu             ###   ########.fr       */
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
		if(!is_identifier(process->cmd[i]))
			return (error_occur("unset", NULL, "not a valid identifier", 1));
		if (find_env(line, process->cmd[i]))
		{
			// if (ft_strncmp(find_env(line, process->cmd[i])->key, "PATH", 5) == 0)
			// 	line->unset_path = 1;
			delete_env(line, process->cmd[i]);
		}
	}
	return (0);
}
