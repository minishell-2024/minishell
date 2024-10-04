/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/03 22:19:12 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_state	handle_general(t_token **tokens, char **buf, char **ptr, int *sq_flag)
{
	char	c;

	c = **ptr;
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>')
	{
		if (ft_strlen(*buf) > 0)
		{
			add_token(tokens, *buf, TOKEN_STRING, *sq_flag);
			*buf = reset_buf(*buf, sq_flag);
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
		add_token(tokens, ft_strdup("|"), TOKEN_PIPE, *sq_flag);
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
		{
			(*ptr)++;
			redirect = ft_strdup(">>");
		}
		else
			redirect = ft_strdup(">");
	}
	else if (**ptr == '<')
	{
		if (*(*ptr + 1) == '<')
		{
			(*ptr)++;
			redirect = ft_strdup("<<");
		}
		else
			redirect = ft_strdup("<");
	}
	return (redirect);
}

char	*reset_buf(char *old_buf, int *sq_flag)
{
	char	*new_buf;

	*sq_flag = 0;
	free(old_buf);
	new_buf = ft_strdup("");
	if (!new_buf)
		common_error("malloc", 0, 0, 0);
	return (new_buf);
}
