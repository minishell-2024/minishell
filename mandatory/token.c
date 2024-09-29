/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 14:33:21 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	handle_general(t_token *tokens, char **buf_ptr, char **ptr)
{
	char	c;

	c = **ptr;
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>')
	{
		if (ft_strlen(*buf_ptr) > 0)
		{
			add_token(&tokens, *buf_ptr);
			*buf_ptr = ft_strdup("");
		}
	}
	else if (c == '\'')
		return (STATE_SQUOTE);
	else if (c == '"')
		return (STATE_DQUOTE);
	else
		*buf_ptr = append_char(*buf_ptr, c);
	if (c == '|')
		add_token(&tokens, ft_strdup("|"), TOKEN_PIPE);
	if (c == '<' || c == '>')
		add_token(&tokens, get_special_char(ptr), TOKEN_REDIRECT);
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

char	*append_char(char *buf, char c)
{
	char	*new;
	int		size;

	size = ft_strlen(buf);
	new = (char *)malloc(sizeof(char) * (size + 2));
	if (!new)
	{
		free(buf);
		return (FAIL);	
	}
	memcpy(new, buf, size);
	new[size] = c;
	new[size + 1] = 0;
	free(buf);
	return (new);
}

char	*get_special_char(char **ptr)
{
	char	c;

	c = **ptr;
	if (c == '>')
	{
		if (*(*ptr + 1) == '>')
		{
			(*ptr)++;
			return (ft_strdup(">>"));
		}
		return (ft_strdup(">"));
	}
	if (c == '<')
	{
		if (*(*ptr + 1) == '<')
		{
			(*ptr)++;
			return (ft_strdup("<<"));
		}
		return (ft_strdup("<"));
	}
	return (FAIL);
}

int	add_token(t_token **token_addr, char *str, t_tokentype token_type)
{
	t_token	*new;
	t_token	*tokens;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (FAIL);
	new->word = str;
	new->type = token_type;
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
