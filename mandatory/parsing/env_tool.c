/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:54:17 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/04 22:29:36 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_env	*get_key_value(char **envp)
{
	t_env	*new_node;
	char	*equal;
	char	*key;
	char	*value;

	value = 0;
	equal = ft_strchr(*envp, '=');
	if (equal)
	{
		key = ft_substr(*envp, 0, equal - *envp);
		value = ft_substr(equal, 1, ft_strlen(*envp) - ft_strlen(key) - 1);
		if (!value)
			common_error("malloc", 0, 0, 0);
	}
	else
		key = ft_strdup(*envp);
	if (!key)
		common_error("malloc", 0, 0, 0);
	new_node = create_env_node(key, value);
	if (!new_node)
		common_error("malloc", 0, 0, 0);
	free(key);
	free(value);
	return (new_node);
}

char	**new_envp(t_env *env)
{
	t_env	*ptr;
	char	**envp;
	int		size;

	size = 0;
	ptr = env;
	while (ptr)
	{
		size++;
		ptr = ptr->env_next;
	}
	envp = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!envp)
		common_error("malloc", 0, 0, 0);
	return (envp);
}
