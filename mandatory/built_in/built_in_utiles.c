/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:27:08 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 18:57:42 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	env_len(t_line *line)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = line->env;
	while (temp)
	{
		i++;
		temp = temp->env_next;
	}
	return (i);
}

int	is_identifier(char *str)
{
	int	length;
	int	i;

	i = 0;
	length = ft_strlen(str);
	if (!str)
		return (0);
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (0);
	while (++i < length)
	{
		if (str[i] != '_' && !ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

t_env	*divide_env_key_value(char *str)
{
	t_env	*env;
	char	*equal;

	env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!env)
		common_error("malloc", NULL, NULL, 1);
	equal = ft_strchr(str, '=');
	if (equal)
	{
		env->key = ft_substr(str, 0, equal - str);
		if (!env->key)
			common_error("malloc", NULL, NULL, 1);
		env->value
			= ft_substr(equal, 1, ft_strlen(str) - ft_strlen(env->key) - 1);
		if (!env->value)
			common_error("malloc", NULL, NULL, 1);
	}
	else
		env->key = ft_strdup(str);
	if (!env->key)
		common_error("malloc", NULL, NULL, 1);
	return (env);
}
