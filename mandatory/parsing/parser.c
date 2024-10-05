/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 04:47:01 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/05 18:40:16 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_process	*parse_pipe(t_token **ptr, int *flag, t_line *line)
{
	t_process		*new_proc_node;
	t_redirection	*new_redir_node;
	char			**left;

	if (!*ptr)
		return (FAIL);
	new_redir_node = 0;
	left = parse_command(ptr, &new_redir_node, flag, line);
	if (!left && !new_redir_node)
	{
		if (*ptr && *flag != SYNTAX_ERROR)
			*flag = syntax_error(line, *ptr, SYNTAX_ERROR);
		return (0);
	}
	new_proc_node = create_process_node();
	if (!new_proc_node)
		common_error("malloc", 0, 0, 0);
	new_proc_node->cmd = left;
	new_proc_node->redirect_node = new_redir_node;
	if (*flag == FAIL)
		return (new_proc_node);
	consume_token(ptr);
	new_proc_node->process_next = parse_pipe(ptr, flag, line);
	return (new_proc_node);
}

char	**parse_command(t_token **ptr, t_redirection **redirect, \
						int *flag, t_line *line)
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
			*flag = append_redir(redirect, ptr, redir_type, line);
			if (*flag == SYNTAX_ERROR)
				return (commands);
		}
		else if ((*ptr)->type == TOKEN_STRING)
			commands = append_simple_cmd(commands, ptr);
	}
	return (commands);
}

int	append_redir(t_redirection **head, t_token **ptr, \
					int redir_type, t_line *line)
{
	t_redirection	*new_redir_node;
	t_redirection	*last;
	char			*file;

	if (!*ptr || (*ptr)->type != TOKEN_STRING)
		return (syntax_error(line, *ptr, SYNTAX_ERROR));
	new_redir_node = create_redir_node(redir_type);
	file = ft_strdup((*ptr)->word);
	if (!file)
		common_error("malloc", 0, 0, 0);
	if (redir_type == REDIR_DELIMIT)
		new_redir_node->here_doc_eof = file;
	else
		new_redir_node->file_name = file;
	consume_token(ptr);
	last = *head;
	if (!*head)
	{
		*head = new_redir_node;
		return (SUCCESS);
	}
	while (last->redirect_next)
		last = last->redirect_next;
	last->redirect_next = new_redir_node;
	return (SUCCESS);
}

char	**append_simple_cmd(char **cmd, t_token **ptr)
{
	char	**new;
	int		idx;

	idx = 0;
	new = new_cmd_list(cmd);
	while (cmd && cmd[idx])
	{
		new[idx] = cmd[idx];
		idx++;
	}
	new[idx] = ft_strdup((*ptr)->word);
	if (!new[idx])
		common_error("malloc", 0, 0, 0);
	consume_token(ptr);
	new[idx + 1] = 0;
	free(cmd);
	return (new);
}

char	**new_cmd_list(char	**old_cmd)
{
	int		height;
	char	**new;

	height = 0;
	if (old_cmd)
	{
		while (old_cmd[height])
			height++;
	}
	height++;
	new = (char **)ft_calloc(sizeof(char *), (height + 1));
	if (!new)
		common_error("malloc", 0, 0, 0);
	return (new);
}
