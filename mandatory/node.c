/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:10:34 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 16:43:52 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*create_process_node()
{
	t_process	*new_node;

	new_node = (t_process *)malloc(sizeof(t_process));
	if (!new_node)
		return (FAIL);
	ft_bzero(new_node, sizeof(t_process));
	return (new_node);
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

int	which_redir(t_tokentype token_type)
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
