/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/05 05:16:51 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	add_token(t_token **token, char *str, t_tokentype token_type)
{
	t_token	*new;
	t_token	*curr;

	new = create_token_node(token_type);
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

t_state	handle_general(t_token **tokens, char **buf, char **ptr)
{
	char	c;

	c = **ptr;
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>')
	{
		if (ft_strlen(*buf) > 0)
		{
			add_token(tokens, *buf, TOKEN_STRING);
			*buf = reset_buf();
		}
	}
	else if (c == '<')
		handle_out_redir(tokens, ptr);
	else if (c == '\'')
		return (STATE_SQUOTE);
	else if (c == '"')
		return (STATE_DQUOTE);
	else
		*buf = append_char(*buf, c);
	if (c == '|')
		add_token(tokens, get_pipe(), TOKEN_PIPE);
	if (c == '>')
		add_token(tokens, get_redirect(ptr), TOKEN_REDIRECT);
	return (STATE_GENERAL);
}

t_state	handle_quote(t_state state, char **curr, char **buf_ptr, t_line *input)
{
	if (state == STATE_SQUOTE && **curr == '\'')
		return (STATE_GENERAL);
	if (state == STATE_DQUOTE && **curr == '"')
		return (STATE_GENERAL);
	if (state == STATE_DQUOTE && **curr == '$')
		handle_dollar(buf_ptr, curr, input);
	else
		*buf_ptr = append_char(*buf_ptr, **curr);
	return (state);
}


void	handle_dollar(char **buf, char **curr, t_line *input)
{
	char	*key;
	char	*value;
	int		key_size;

	key = read_word(*curr + 1);
	key_size = ft_strlen(key) + 1;
	value = find_env_value(input, key);
	while (*value)
	{
		*buf = append_char(*buf, *value);
		value++;
	}
	*curr += key_size;
	free(key);
}

void	handle_out_redir(t_token **tokens, char **curr)
{
	char	*redir;
	char	*eof;

	redir = get_redirect(curr);
	add_token(tokens, redir, TOKEN_REDIRECT);
	if (which_redir(redir) == REDIR_DELIMIT)
	{
		while (*curr && ft_isspace(**curr))
			(*curr)++;
		while (*curr && !ft_isspace(**curr))
		{
			eof = append_char(eof, **curr);
			(*curr)++;
		}
		if (eof)
			add_token(tokens, eof, TOKEN_STRING);
	}
}
