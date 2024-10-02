/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:21:44 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/02 21:52:20 by jihyjeon         ###   ########.fr       */
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

int	make_env(t_line *line, char **envp)
{
	char	*key;
	char	*value;
	char	*equal;

	while (*envp)
	{
		value = 0;
		equal = ft_strchr(*envp, '=');
		if (equal)
		{
			key = ft_substr(*envp, 0, equal - *envp);
			value = ft_substr(equal, 1, ft_strlen(*envp) - ft_strlen(key) - 1);
		}
		else
			key = ft_strdup(*envp);
		insert_env(line, key, value);
		free(key);
		if (value)
			free(value);
		envp++;
	}
	insert_env(line, "?", "0"); //$? handling
	change_env_value(line, "_", ft_strdup("minishell")); //replace key:_ 's value
	return (SUCCESS);
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
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
		exit(FAIL); //malloc
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
			curr->value = new_value;
			free(old_value);
			changed = SUCCESS;
			break ;
		}
		curr = curr->env_next;
	}
	return (changed);
}
