/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:21:44 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/03 16:43:17 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	insert_env(t_line *line, char *key, char *value)
{
	t_env	*curr;
	t_env	*new_node;

	curr = line->env;
	new_node = create_env_node(key, value);
	if (!new_node)
		common_error("malloc", 0, 0, 0);
	if (!curr)
		line->env = new_node;
	else
	{
		while (curr->env_next)
			curr = curr->env_next;
		curr->env_next = new_node;
	}
	return (SUCCESS);
}

t_env	*make_env(char **envp)
{
	t_env	*env;
	t_env	*curr;
	t_env	*new_node;

	env = 0;
	while (*envp)
	{
		curr = env;
		new_node = get_key_value(envp);
		if (!env)
			env = new_node;
		else
		{
			while (curr->env_next)
				curr = curr->env_next;
			curr->env_next = new_node;
		}
		envp++;
	}
	return (env);
}

char	**make_envp(t_env *env)
{
	t_env	*ptr;
	int		size;
	char	**envp;

	size = 0;
	ptr = env;
	while (ptr)
	{
		size++;
		ptr = ptr->env_next;
	}
	envp = (char **)ft_calloc(sizeof(char *) * (size + 1), 1);
	if (!envp)
		common_error("malloc", 0, 0, 0);
	while (env)
	{
		*envp = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		envp++;
		env = env->env_next;
	}
	*envp = 0;
	//free t_env?
	return (envp);
}

int	change_env_value(t_line *line, char *key, char *new_value)
{
	t_env	*curr;
	char	*old_value;
	int		changed;

	curr = line->env;
	changed = FAIL;
	while (curr)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(curr->key)) == 0)
		{
			old_value = curr->value;
			curr->value = ft_strdup(new_value);
			if (!curr->value)
				common_error("malloc", 0, 0, 0);
			free(old_value);
			changed = SUCCESS;
			break ;
		}
		curr = curr->env_next;
	}
	return (changed);
}

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
