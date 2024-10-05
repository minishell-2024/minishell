/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:38:24 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 15:59:43 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	execute_env(t_line *line)
{
	t_env	*env;

	env = line->env;
	while (env)
	{
		if (ft_strncmp(env->key, "?", 2) != 0 && env->value) // 나중에 예외있는지 체크해보기
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			if (ft_strncmp(env->key, "_", 2) == 0)
				ft_putendl_fd("/usr/bin/env", STDOUT_FILENO);
			else
				ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->env_next;
	}
	return (0);
}
