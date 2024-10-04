/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:10:34 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/04 23:08:23 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_token	*create_token_node(t_tokentype type, int sq_flag)
{
	t_token	*new;

	new = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!new)
		common_error("malloc", 0, 0, 0);
	new->type = type;
	new->squote_flag = sq_flag;
	return (new);
}

t_process	*create_process_node(void)
{
	t_process	*new_node;

	new_node = (t_process *)ft_calloc(sizeof(t_process), 1);
	if (!new_node)
		common_error("malloc", 0, 0, 0);
	return (new_node);
}

t_redirection	*create_redir_node(int redir_type, char *file)
{
	t_redirection	*new_node;

	new_node = (t_redirection *)ft_calloc(sizeof(t_redirection), 1);
	if (!new_node)
		common_error("malloc", 0, 0, 0);
	new_node->type = redir_type;
	return (new_node);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		common_error("malloc", 0, 0, 0);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		common_error("malloc", 0, 0, 0);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			common_error("malloc", 0, 0, 0);
	}
	return (new_node);
}

int	which_redir(char *word)
{
	int	size;

	size = ft_strlen(word) + 1;
	if (ft_strncmp(word, "<", size) == 0)
		return (REDIR_INPUT);
	if (ft_strncmp(word, "<<", size) == 0)
		return (REDIR_DELIMIT);
	if (ft_strncmp(word, ">", size) == 0)
		return (REDIR_OUTPUT);
	if (ft_strncmp(word, ">>", size) == 0)
		return (REDIR_APPEND);
	return (-1);
}
