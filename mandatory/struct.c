/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/13 20:38:11 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_token(t_token **token_addr, char *str)
{
	t_token	*new;
	t_token	*tokens;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (FAIL);
	new->word = str;
	new->next = 0;
	if (!*token_addr)
	{
		*token_addr = new;
		return (SUCCESS);
	}
	tokens = *token_addr;
	while (tokens)
	{
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
	}
	tokens->next = new;
	return (SUCCESS);
}

int	delete_tokens(t_token **tokens)
{

}