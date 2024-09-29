/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:21:44 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 22:44:13 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insert_env(t_line *line, char *key, char *value)
{
	
}

t_env	*make_env(char **envp)
{
	t_env	*head;
	t_env	*curr;
	t_env	*new_node;
	char	**set;
	int		idx;

	idx = 0;
	head = 0;
	while (envp[idx])
	{
		set = ft_split(envp[idx], '=');
		new_node = create_env_node();
		new_node->key = set[0];
		new_node->value = set[1];
		if (!head)
		{
			head = new_node;
			curr = head;
		}
		else
			curr->env_next = new_node;
		free(set);
		idx++;
	}
	return (head);
}

char	**make_envp(t_env *env)
{

}
