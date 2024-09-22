/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:07:01 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/22 21:45:29 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"
#include "minishell.h"

int	change_PWD(t_line *line, char *path)
{
	t_env	*env;

	env = find_env(line, "PWD");
	if (env)
	{
		if (env->value)
			free(env->value);
		env->value = path;
		return (0);
	}
	else
		return (insert_env("PWD", path)); // 이부분 미완... 함수 있으면 이용할 것.
}

int	execute_cd(t_line *line, t_process *process)
{
	if (!process->cmd[1])
		// return (change_OLDPWD(line, ));
	if (process->cmd[1])
}
