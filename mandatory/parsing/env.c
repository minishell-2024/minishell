/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:21:44 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/04 21:54:26 by jihyjeon         ###   ########.fr       */
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
	char	**curr;

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
	curr = envp;
	while (env)
	{
		*curr = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		curr++;
		env = env->env_next;
	}
	*curr = 0;
	//free t_env?
	return (envp);
}

void	init_env(t_line *line, char **envp)
{
	t_env	*question;
	t_env	*under_bar;

	line->env = make_env(envp);
	question = find_env(line, "?");
	if (question)
		change_env_value(line, "?", "0");
	else
		insert_env(line, "?", "0");
	under_bar = find_env(line, "_");
	if (under_bar)
		change_env_value(line, "_", "minishell");
	else
		insert_env(line, "_", "minishell");
}

int	change_env_value(t_line *line, char *key, char *value)
{
	t_env	*curr;
	char	*old_value;
	char	*new_value;
	int		changed;

	curr = line->env;
	changed = FAIL;
	while (curr)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(curr->key) + 1) == 0)
		{
			old_value = curr->value;
			new_value = ft_strdup(value);
			if (!new_value)
				common_error("malloc", 0, 0, 0);
			curr->value = new_value;
			free(old_value);
			changed = SUCCESS;
			break ;
		}
		curr = curr->env_next;
	}
	return (changed);
}
