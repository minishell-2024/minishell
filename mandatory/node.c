/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:10:34 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/23 05:10:42 by jihyjeon         ###   ########.fr       */
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

t_redirect	*create_redir_node(t_tokentype redir_type)
{

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
