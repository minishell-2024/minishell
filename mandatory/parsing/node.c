/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:10:34 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/02 19:18:24 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_token	*create_token_node(t_tokentype type, int sq_flag)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (FAIL);
	ft_bzero(new, 0);
	new->type = type;
	new->squote_flag = sq_flag;
	return (new);
}

t_process	*create_process_node(void)
{
	t_process	*new_node;

	new_node = (t_process *)malloc(sizeof(t_process));
	if (!new_node)
		return (FAIL);
	ft_bzero(new_node, sizeof(t_process));
	return (new_node);
}

t_redirection	*create_redir_node(int redir_type)
{
	t_redirection	*new_node;

	new_node = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_node)
		return (FAIL);
	ft_bzero(new_node, sizeof(t_redirection));
	new_node->type = redir_type;
	return (new_node);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (FAIL);
	ft_bzero(new_node, sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	return (new_node);
}

int	which_redir(char *word)
{
	int	size;

	size = ft_strlen(word);
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

// void	free_old_cmds(char **cmd)
// {
// 	int	i;

// 	i = 0;
// 	if (!cmd)
// 		return ;
// 	while (cmd[i])
// 	{
// 		free(cmd[i]);
// 		i++;
// 	}
// 	free(cmd);
// }
