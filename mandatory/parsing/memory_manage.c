/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:27:14 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/04 16:05:59 by jihyjeon         ###   ########.fr       */
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
