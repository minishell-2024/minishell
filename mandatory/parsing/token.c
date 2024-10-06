/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/05 10:17:46 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	add_token(t_token **token, char *str, t_tokentype token_type)
{
	t_token	*new;
	t_token	*curr;

	if (ft_strlen(str) == 0)
		return ;
	new = create_token_node(token_type, str);
	if (!*token)
	{
		*token = new;
		return ;
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
	return ;
}

t_state	handle_general(t_token **tokens, char **buf, char **ptr)
{
	char	c;

	c = **ptr;
	if (ft_isspace(c) || c == '|')
		*buf = push_and_reset(tokens, *buf, TOKEN_STRING);
	else if (c == '\'')
		return (STATE_SQUOTE);
	else if (c == '"')
		return (STATE_DQUOTE);
	else if (c == '<' || c == '>')
		return (handle_redir(tokens, ptr, buf, STATE_GENERAL));
	else
		*buf = append_char(*buf, c);
	if (c == '|')
		add_token(tokens, "|", TOKEN_PIPE);
	return (STATE_GENERAL);
}

t_state	handle_quote(t_state state, char **curr, char **buf_ptr, t_line *input)
{
	if (state == STATE_SQUOTE && **curr == '\'')
		return (STATE_GENERAL);
	if (state == STATE_DQUOTE && **curr == '"')
		return (STATE_GENERAL);
	if (state == STATE_QHEREDOC && (**curr == '\'' || **curr == '"'))
		return (STATE_HEREDOC);
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
	key_size = ft_strlen(key);
	value = find_env_value(input, key);
	if (!value)
	{
		free(key);
		*curr += key_size;
		return ;
	}
	while (*value)
	{
		*buf = append_char(*buf, *value);
		value++;
	}
	*curr += key_size;
	free(key);
}

t_state	handle_redir(t_token **tokens, char **curr, char **buf, t_state state)
{
	char			*redir;
	t_redir_type	type;

	if (**curr == '<' || **curr == '>')
	{
		*buf = push_and_reset(tokens, *buf, TOKEN_STRING);
		redir = get_redirect(curr);
		add_token(tokens, redir, TOKEN_REDIRECT);
		type = which_redir(redir);
		free(redir);
		if (type != REDIR_DELIMIT)
			return (STATE_GENERAL);
		while (ft_isspace(*(*curr + 1)))
			(*curr)++;
	}
	else if (state != STATE_QHEREDOC && ft_isspace(**curr))
	{
		*buf = push_and_reset(tokens, *buf, TOKEN_STRING);
		return (STATE_GENERAL);
	}
	else if (**curr == '"' || **curr == '\'')
		return (STATE_QHEREDOC);
	else
		*buf = append_char(*buf, **curr);
	return (STATE_HEREDOC);
}
