/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:04:28 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 21:11:52 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	buf = ft_strdup("");
	state = STATE_GENERAL;
	curr = line;
	while (*curr)
	{
		if (state == STATE_GENERAL)
			state = handle_general(tokens, &buf, &curr);
		else if (state == STATE_SQUOTE || state == STATE_DQUOTE)
			state = handle_quote(state, *curr, &buf);
		curr++;
	}
	if (ft_strlen(buf) > 0)
		add_token(tokens, buf, TOKEN_STRING);
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
		if (curr->type == TOKEN_STRING)
			replace_env(curr, env);
		curr = curr->next;
	}
	curr = tokens;
	process = parse_pipe(&curr);
	return (process);
}
