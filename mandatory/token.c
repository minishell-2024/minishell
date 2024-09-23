/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/23 19:59:45 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	handle_general(t_token *tokens, char **buf_ptr, char *ptr)
{
	char	c;
	char	*buf;

	c = *ptr;
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
		add_token(&tokens, get_redirect(ptr));
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

int	add_token(t_token **token_addr, char *str)
{
	t_token	*new;
	t_token	*tokens;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (FAIL);
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

t_tokentype	get_tokentype(char *str)
{
	if (!str || !*str)
		return (TOKEN_END);
	if (ft_strncmp("|", str, ft_strlen(str)) == 0)
		return (TOKEN_PIPE);
	if (ft_strncmp("<<", str, ft_strlen(str)) == 0)
		return (TOKEN_DELIMIT);
	if (ft_strncmp(">>", str, ft_strlen(str)) == 0)
		return (TOKEN_APPEND);
	if (ft_strncmp("<", str, ft_strlen(str)) == 0)
		return (TOKEN_INPUT);
	if (ft_strncmp(">", str, ft_strlen(str)) == 0)
		return (TOKEN_OUTPUT);
	if (*str == '"')
		return (TOKEN_DQUOTE);
	if (*str == '\'')
		return (TOKEN_QUOTE);
	return (TOKEN_STRING);
}

int	delete_tokens(t_token **tokens)
{

}
