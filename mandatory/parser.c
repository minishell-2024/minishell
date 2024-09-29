/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 04:47:01 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 17:25:38 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*parse_pipe(t_token **ptr)
{
	t_process		*new_proc_node;
	t_redirection	*new_redir_node;
	char			**left;

	if (!*ptr)
		return (FAIL);
	new_redir_node = 0;
	left = parse_command(ptr, &new_redir_node);
	if (left == FAIL)
		return (FAIL); // syntax error near unexpected token `|' (also should consider free)
	new_proc_node = create_process_node();
	if (!new_proc_node)
		exit(FAIL); //malloc
	consume_token(ptr);
	new_proc_node->cmd = left;
	new_proc_node->redirect_node = new_redir_node;
	new_proc_node->process_next = parse_pipe(ptr);
	return (new_proc_node);
}

char	**parse_command(t_token **ptr, t_redirection **redirect)
{
	char	**commands;

	commands = 0;
	while (*ptr && (*ptr)->type != TOKEN_PIPE)
	{
		if ((*ptr)->type == TOKEN_REDIRECT)
			append_redir(redirect, ptr);
		else if ((*ptr)->type == TOKEN_STRING)
			append_simple_cmd(commands, ptr);
	}
	return (commands);
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
