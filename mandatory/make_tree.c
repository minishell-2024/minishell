/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 04:47:01 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/23 04:43:14 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_pipe(t_token **ptr)
{
	t_ast_node	*node;
	t_ast_node	*left;

	left = parse_command(ptr);
	if (*ptr && (*ptr)->token_type == TOKEN_PIPE)
	{
		if (left == FAIL)
			return (FAIL); // syntax error near unexpected token `|' (also should consider free)
		node = create_new_node(NODE_PIPE);
		if (!node)
			exit(FAIL); //malloc
		consume_token(ptr);
		node->left = left;
		node->right = parse_pipe(ptr);
		left = node;
	}
	return (left);
}

t_ast_node	*parse_command(t_token **ptr)
{
	t_ast_node	*node;
	t_command	*cmd;

	node = create_new_node(NODE_COMMAND);
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!node || !cmd)
		exit(FAIL); //msg, exit, malloc free
	while (*ptr && (*ptr)->token_type != TOKEN_PIPE)
	{
		if (is_redir((*ptr)->token_type) == SUCCESS)
			append_redir(cmd, ptr);
		else
			append_simple_cmd(cmd, ptr);
	}
	node->data = cmd;
	if (!cmd->redirect && !cmd->simple_cmd)
	{
		free(cmd);
		free(node);
		node = 0;
	}
	return (node);
}

t_redirect	*append_redir(t_command *cmd, t_token **ptr)
{
	t_redirect	*redir;

	redir->type = tokens->token_type;
	redir->next_redir = parse_redir(tokens);
	return (redir);
}

t_ast_node	*parse_simple_cmd(t_command *cmd, t_token **ptr)
{
	t_simple_cmd	*simple_cmd;

	return (simple_cmd);
}
