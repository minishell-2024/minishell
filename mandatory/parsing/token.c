/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/04 18:13:11 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	add_token(t_token **token, char *str, t_tokentype token_type, int sq_flag)
{
	t_token	*new;
	t_token	*curr;

	new = create_token_node(token_type, sq_flag);
	if (!new)
		common_error("malloc", 0, 0, 0);
	new->word = ft_strdup(str);
	if (!new->word)
		common_error("malloc", 0, 0, 0);
	free(str);
	if (!*token)
	{
		*token = new;
		return (SUCCESS);
	}
	curr = *token;
	while (curr)
	{
		if (curr->next)
			curr = curr->next;
		else
			break ;
	}
	curr->next = new;
	return (SUCCESS);
}

t_state	handle_general(t_token **tokens, char **buf, char **ptr, int *sq_flag)
{
	char	c;

	c = **ptr;
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>')
	{
		if (ft_strlen(*buf) > 0)
		{
			add_token(tokens, *buf, TOKEN_STRING, *sq_flag);
			*buf = reset_buf(sq_flag);
		}
	}
	else if (c == '\'')
	{
		*sq_flag = 1;
		return (STATE_SQUOTE);
	}
	else if (c == '"')
		return (STATE_DQUOTE);
	else
		*buf = append_char(*buf, c);
	if (c == '|')
		add_token(tokens, get_pipe(), TOKEN_PIPE, *sq_flag);
	if (c == '<' || c == '>')
		add_token(tokens, get_redirect(ptr), TOKEN_REDIRECT, *sq_flag);
	return (STATE_GENERAL);
}

t_state	handle_quote(t_state state, char c, char **buf_ptr, t_line *input)
{
	if (state == STATE_SQUOTE && c == '\'')
		return (STATE_GENERAL);
	if (state == STATE_DQUOTE && c == '"')
	{
		*buf_ptr = key_to_value(*buf_ptr, input);
		return (STATE_GENERAL);
	}
	*buf_ptr = append_char(*buf_ptr, c);
	return (state);
}

char	*append_char(char *buf, char c)
{
	char	*new;
	int		size;

	size = ft_strlen(buf);
	new = (char *)ft_calloc(sizeof(char), size + 2);
	if (!new)
		common_error("malloc", 0, 0, 0);
	ft_memcpy(new, buf, size);
	new[size] = c;
	new[size + 1] = 0;
	free(buf);
	return (new);
}

char	*get_redirect(char **ptr)
{
	char	*redirect;

	redirect = 0;
	if (**ptr == '>')
	{
		if (*(*ptr + 1) == '>')
			redirect = ft_strdup(">>");
		else
			redirect = ft_strdup(">");
	}
	else if (**ptr == '<')
	{
		if (*(*ptr + 1) == '<')
			redirect = ft_strdup("<<");
		else
			redirect = ft_strdup("<");
	}
	if (!redirect)
		common_error("malloc", 0, 0, 0);
	if (ft_strlen(redirect) > 1)
		(*ptr)++;
	return (redirect);
}
