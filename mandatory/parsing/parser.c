/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 04:47:01 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/04 16:23:08 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	consume_token(t_token **ptr);

t_process	*parse_pipe(t_token **ptr)
{
	t_process		*new_proc_node;
	t_redirection	*new_redir_node;
	char			**left;

	if (!*ptr)
		return (FAIL);
	new_redir_node = 0;
	left = parse_command(ptr, &new_redir_node);
	if (!left && !new_redir_node)
	{
		if ((*ptr)->type == TOKEN_PIPE)
		{
			error_occur(0, 0, "syntax error near unexpected token `|'", 0);
			return (FAIL);
		}
	}
	new_proc_node = create_process_node();
	if (!new_proc_node)
		common_error("malloc", 0, 0, 0);
	consume_token(ptr);
	new_proc_node->cmd = left;
	new_proc_node->redirect_node = new_redir_node;
	new_proc_node->process_next = parse_pipe(ptr);
	return (new_proc_node);
}

char	**parse_command(t_token **ptr, t_redirection **redirect)
{
	char	**commands;
	int		redir_type;

	commands = 0;
	while (*ptr && (*ptr)->type != TOKEN_PIPE)
	{
		if ((*ptr)->type == TOKEN_REDIRECT)
		{
			redir_type = which_redir((*ptr)->word);
			consume_token(ptr);
			append_redir(redirect, ptr, redir_type);
		}
		else if ((*ptr)->type == TOKEN_STRING)
			commands = append_simple_cmd(commands, ptr);
	}
	return (commands);
}

void	append_redir(t_redirection **head, t_token **ptr, int redir_type)
{
	t_redirection	*new_redir_node;
	t_redirection	*last;

	if (!*ptr || (*ptr)->type != TOKEN_STRING)
		common_error(0, 0, "syntax error near string", 0);
	new_redir_node = create_redir_node(redir_type);
	if (redir_type == REDIR_DELIMIT)
		new_redir_node->here_doc_eof = (*ptr)->word;
	else
		new_redir_node->file_name = (*ptr)->word;
	consume_token(ptr);
	last = *head;
	if (!last)
	{
		*head = new_redir_node;
		return ;
	}
	while (last->redirect_next)
		last = last->redirect_next;
	last->redirect_next = new_redir_node;
}

char	**append_simple_cmd(char **cmd, t_token **ptr)
{
	char	**new;
	int		height;
	int		idx;

	height = 0;
	if (cmd)
	{
		while (cmd[height])
			height++;
	}
	height++;
	new = (char **)ft_calloc(sizeof(char *), (height + 1));
	if (!new)
		common_error("malloc", 0, 0, 0);
	idx = 0;
	while (cmd && cmd[idx])
	{
		new[idx] = cmd[idx];
		idx++;
	}
	new[idx] = (*ptr)->word;
	consume_token(ptr);
	new[height] = 0;
	free(cmd);
	return (new);
}

void	consume_token(t_token **ptr)
{
	if (!ptr || !*ptr)
		return ;
	*ptr = (*ptr)->next;
}


 // syntax error near unexpected token `|' (also should consider free)
