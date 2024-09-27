/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:12:03 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/27 22:21:18 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"
#include "minishell.h"

int	print_env_with_quote(t_line *line, t_process *process)
{
	t_env	*env;

	env = line->env;
	while (env)
	{
		if (ft_strncmp(env->key, "?", 2) != 0)
		{
			if (!env->value)
				ft_putendl_fd(env->key, STDIN_FILENO);
			else
			{
				ft_putstr_fd(env->key, STDIN_FILENO);
				ft_putstr_fd("=\"", STDIN_FILENO);
				ft_putstr_fd(env->value, STDIN_FILENO);
				ft_putendl_fd("\"", STDIN_FILENO);
			}
		}
		env = env->env_next;
	}
	return (0);
}

int	insert_env_by_str(t_line *line, t_process *process, char *str)
{
	//
}

int	execute_export(t_line *line, t_process *process)
{
	int	i;

	i = 0;
	if (!process->cmd[1])
		return (print_env_with_quote(line, process));
	while (process->cmd[++i])
	{
		// 입력을 먼저 key, value로 분할해야할수도 value는 identifier룰을 따르지 않아도 ㄱㅊ음...
		// if (!is_identifier(process->cmd[i]))
		// {
		// 	error_occur("export", NULL, "not a valid identifier", 1);
		// 	continue ;
		// }
		// insert_env_by_str(line, process, process->cmd[i]); // return 여부 생각해보기
	}
}
