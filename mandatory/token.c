/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 12:18:18 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	handle_general(t_token *tokens, char **buf_ptr, char **ptr)
{
	char	c;
	char	*buf;

	c = **ptr;
	buf = *buf_ptr;
	if (ft_isspace(c) || special_char(c))
	{
		if (ft_strlen(buf) > 0)
		{
			add_token(&tokens, buf);
			buf = ft_strdup("");
		}
	}
	else if (c == '\'')
		return (STATE_SQUOTE);
	else if (c == '"')
		return (STATE_DQUOTE);
	else
		*buf_ptr = append_char(buf, c);
	if (special_char(c))
		add_token(&tokens, get_special_char(ptr));
	return (STATE_GENERAL);
}

t_state	handle_quote(t_state state, char c, char **buf_ptr)
{
	if (state == STATE_SQUOTE && c == '\'')
		return (STATE_GENERAL);
	if (state == STATE_DQUOTE && c == '"')
		return (STATE_GENERAL);
	*buf_ptr = append_char(*buf_ptr, c);
	return (state);
}

int	special_char(char c)
{
	if (c == '|')
		return (SUCCESS);
	if (c == '>' || c == '<')
		return (SUCCESS);
	return (FAIL);
}

char	*get_special_char(char **ptr)
{
	char	c;
	char	next_c;

	c = **ptr;
	next_c = *(*ptr + 1);
	if (c == '|')
		return (ft_strdup("|"));
	if (c == '>')
	{
		if (next_c == '>')
			return (ft_strdup(">>"));
		return (ft_strdup(">"));
	}
	if (c == '<')
	{
		if (next_c == '<')
			return (ft_strdup("<<"));
		return (ft_strdup("<"));
	}
	return (FAIL);
}

int	add_token(t_line *input, char *str)
{
	new->word = ft_strdup(str);
	new->token_type = get_tokentype(str);
	new->next = 0;
	free(str);
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
