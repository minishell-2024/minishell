/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:27:08 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/06 17:28:31 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_env	*find_env(t_line *line, char *key)
{
	t_env	*dummy;

	dummy = line->env;
	while (dummy)
	{
		if (!ft_strncmp(dummy->key, key, ft_strlen(key) + 1))
			return (dummy);
		dummy = dummy->env_next;
	}
	return (0);
}

char	*find_env_value(t_line *line, char *key)
{
	t_env	*dummy;

	dummy = line->env;
	while (dummy)
	{
		if (!ft_strncmp(dummy->key, key, ft_strlen(key) + 1))
			return (dummy->value);
		dummy = dummy->env_next;
	}
	return (0);
}

void	swap_env(t_env *env1, t_env *env2)
{
	char	*key;
	char	*value;

	key = env1->key;
	value = env1->value;
	env1->key = env2->key;
	env1->value = env2->value;
	env2->key = key;
	env2->value = value;
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

int	delete_env(t_line *line, char *key)
{
	t_env	*dummy;
	t_env	*trash;

	dummy = line->env;
	if (!line->env)
		return (0);
	if (!ft_strncmp(line->env->key, key, ft_strlen(key) + 1))
	{
		line->env = dummy->env_next;
		free_env(dummy);
		return (1);
	}
	while (dummy->env_next)
	{
		if (!ft_strncmp(dummy->env_next->key, key, ft_strlen(key) + 1))
		{
			trash = dummy->env_next;
			dummy->env_next = dummy->env_next->env_next;
			free_env(trash);
			return (1);
		}
		dummy = dummy->env_next;
	}
	return (0);
}
