/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:27:14 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/04 16:34:00 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*node;

	if (!tokens || !*tokens)
		return ;
	while ((*tokens)->next)
	{
		node = (*tokens);
		if (node->type == TOKEN_PIPE || node->type == TOKEN_REDIRECT)
			free(node->word);
		*tokens = (*tokens)->next;
		free(node);
	}
	node = *tokens;
	*tokens = 0;
	free(node);
}

void	free_process(t_process **proc)
{
	t_process *node;
	
	if (!proc || !*proc)
		return ;
	while ((*proc)->process_next)
	{
		node = (*proc);
		free_old_cmds((*proc)->cmd);
		free_redirection(&((*proc)->redirect_node));
		(*proc) = (*proc)->process_next;
		free(node);
	}
}

void	free_old_cmds(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_redirection(t_redirection **redir)
{
	t_redirection	*node;

	if (!redir || !*redir)
		return ;
	while ((*redir)->redirect_next)
	{
		
	}
}