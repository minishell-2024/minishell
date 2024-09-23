/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:10:34 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/23 16:10:11 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_new_node(t_nodetype node_type)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!new_node)
		return (FAIL);
	new_node->type = node_type;
	new_node->left = 0;
	new_node->right = 0;
	new_node->data = 0;
	return (new_node);
}

t_command	*create_cmd_node(void)
{
	t_command	*new_cmd;

	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return (FAIL);
	new_cmd->simple_cmd = 0;
	new_cmd->redirect = 0;
	return (new_cmd);
}

t_redirect	*create_redir_node(t_tokentype redir_type)
{
	t_redirect	*new_redir;

	new_redir = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new_redir)
		return (FAIL);
	new_redir->type = redir_type;
	new_redir->argv = 0;
	new_redir->next_redir = 0;
	return (new_redir);
}

t_simple_cmd	*create_simple_node(void)
{
	t_simple_cmd	*simple_node;

	simple_node = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!simple_node)
		return (FAIL);
	simple_node->argv = 0;
	simple_node->next_simple_cmd = 0;
	return (simple_node);
}

int	is_redir(t_tokentype token_type)
{
	if (token_type == TOKEN_INPUT)
		return (SUCCESS);
	if (token_type == TOKEN_OUTPUT)
		return (SUCCESS);
	if (token_type == TOKEN_DELIMIT)
		return (SUCCESS);
	if (token_type == TOKEN_APPEND)
		return (SUCCESS);
	return (FAIL);
}
