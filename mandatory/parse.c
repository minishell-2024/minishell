/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:04:28 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 12:18:29 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *line, t_env *envp)
{
	t_line	*input;
	t_token	*tokens;

	if (!line || !ft_strlen(line))
		return (FAIL);
	if (check_quote(line) == FAIL)
		return (QUOTE_INCOMPLETE);
	tokenize(line, input);
	lexer(input, envp);
	make_ast(tokens);

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

int	tokenize(char *line, t_line *input)
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
			state = handle_quote(state, *line, &buf);
		line++;
	}
	if (ft_strlen(buf) > 0)
		add_token(input, buf);
	else
		free(buf);
	return (SUCCESS);
}

t_ast_node	*make_ast(t_token *tokens)
{
	t_ast_node	*head;
	t_token		*ptr;

	ptr = tokens;
	head = parse_pipe(tokens, &ptr);
	return (head);
}
