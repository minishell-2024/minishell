/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:04:28 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/03 00:36:35 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	parse(char *line, t_line *input)
{
	t_token	*tokens;

	if (!line || !ft_strlen(line))
		return (FAIL);
	if (check_quote(line) == FAIL)
		return (QUOTE_INCOMPLETE);
	tokens = 0;
	tokenize(line, &tokens);
	input->proc = lexer(tokens, input->env);
	return (SUCCESS);
}

int	check_quote(char *line)
{
	int	quote_flag;
	int	dquote_flag;
	int	i;

	quote_flag = 0;
	dquote_flag = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !dquote_flag)
			quote_flag = !quote_flag;
		else if (line[i] == '"' && !quote_flag)
			dquote_flag = !dquote_flag;
		i++;
	}
	if (quote_flag || dquote_flag)
		return (FAIL);
	return (SUCCESS);
}

int	tokenize(char *line, t_token **tokens)
{
	char	*curr;
	char	*buf;
	t_state	state;
	int		sq_flag;

	buf = reset_buf(&sq_flag);
	state = STATE_GENERAL;
	curr = line;
	while (*curr)
	{
		if (state == STATE_GENERAL)
			state = handle_general(tokens, &buf, &curr, &sq_flag);
		else if (state == STATE_SQUOTE || state == STATE_DQUOTE)
			state = handle_quote(state, *curr, &buf);
		curr++;
	}
	if (ft_strlen(buf) > 0)
		add_token(tokens, buf, TOKEN_STRING, sq_flag);
	else
		free(buf);
	return (SUCCESS);
}

t_process	*lexer(t_token *tokens, t_env *env)
{
	t_process	*process;
	t_token		*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_STRING && curr->squote_flag == 0)
			key_to_value(curr, env);
		curr = curr->next;
	}
	curr = tokens;
	process = parse_pipe(&curr);
	return (process);
}


int	add_token(t_token **token, char *str, t_tokentype token_type, int sq_flag)
{
	t_token	*new;
	t_token	*tokens;

	new = create_token_node(token_type, sq_flag);
	if (!new)
		return (FAIL);
	new->word = str;
	if (!*token)
	{
		*token = new;
		return (SUCCESS);
	}
	tokens = *token;
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
