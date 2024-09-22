/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 04:47:01 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/22 21:58:23 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_pipe(t_token	*tokens, t_token **ptr)
{
	t_ast_node	*node;
	t_ast_node	*left;

	left = parse_command(tokens, ptr);
	if ((*ptr)->token_type == TOKEN_PIPE)
	{
		if (node == FAIL)
			return (FAIL); // syntax error near unexpected token `|' (also should consider free)
		node = (t_ast_node *)malloc(sizeof(t_ast_node));
		if (!node)
			return (FAIL); //malloc free
		node->type = NODE_PIPE;
		*ptr = (*ptr)->next;
		node->left = left;
		node->right = parse_pipe(tokens, ptr);
		left = node;
	}
	return (left);
}

t_ast_node	*parse_command(t_token *tokens, t_token **ptr)
{
	t_ast_node	*node;
	t_command	*cmd;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (FAIL);
	node->type = NODE_COMMAND;
	node->left = 0;
	node->right = 0;
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (FAIL);
	cmd->redirect = parse_redir(tokens, ptr);
	cmd->simple_cmd = parse_simple_cmd(tokens, ptr);
	node->data = cmd;
	if (!cmd->redirect || !cmd->simple_cmd)
	{
		free(cmd);
		free(node);
		node = 0;
	}
	return (node);
}

t_redirect	*parse_redir(t_token *tokens, t_token **ptr)
{
	t_redirect	*redir;

	redir->type = tokens->token_type;
	redir->next_redir = parse_redir(tokens);
	return (redir);
}

t_ast_node	*parse_simple_cmd(t_token *tokens)
{
	t_simple_cmd	*simple_cmd;

	return (simple_cmd);
}
