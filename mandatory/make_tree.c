/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 04:47:01 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/23 16:13:07 by jihyjeon         ###   ########.fr       */
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
	cmd = create_cmd_node();
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

void	append_redir(t_command *cmd, t_token **ptr)
{
	t_redirect	*redir;
	t_redirect	*last;

	redir = create_redir_node((*ptr)->token_type);
	consume_token(ptr);
	if ((*ptr)->token_type == TOKEN_STRING)
		redir->argv = (*ptr)->word;
	else
		; // syntax error
	consume_token(ptr);
	last = cmd->redirect;
	if (!last)
	{
		cmd->redirect = redir;
		return ;
	}
	while (last->next_redir)
		last = last->next_redir;
	last->next_redir = redir;
}

void	append_simple_cmd(t_command *cmd, t_token **ptr)
{
	t_simple_cmd	*new_simple_cmd;
	t_simple_cmd	*last;

	new_simple_cmd = create_simple_node();
	new_simple_cmd->argv = (*ptr)->word;
	consume_token(ptr);
	last = cmd->simple_cmd;
	if (!last)
	{
		cmd->simple_cmd = new_simple_cmd;
		return ;
	}
	while (last->next_simple_cmd)
		last = last->next_simple_cmd;
	last->next_simple_cmd = new_simple_cmd;
}

void	consume_token(t_token **ptr)
{
	*ptr = (*ptr)->next;
}
