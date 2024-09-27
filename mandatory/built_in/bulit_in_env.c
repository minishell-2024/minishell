/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:38:24 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/27 21:08:49 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"
#include "minishell.h"

int	execute_env(t_line *line, t_process *process)
{
	t_env	*env;

	env = line->env;
	while (env)
	{
		if (ft_strncmp(env->key, "?", 2) != 0 && env->value) // 나중에 예외있는지 체크해보기
		{
			ft_putstr_fd(env->key, STDIN_FILENO);
			ft_putstr_fd("=", STDIN_FILENO);
			ft_putendl_fd(env->value, STDIN_FILENO);
		}
		env = env->env_next;
	}
	return (0);
}
