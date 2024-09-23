/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:04:28 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/23 19:55:08 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *line, t_env *envp)
{
	t_token	*tokens;
	int		length;

	if (!line || !ft_strlen(line))
		return (FAIL);
	if (check_quote(line) == FAIL)
		return (QUOTE_INCOMPLETE);
	tokens = tokenize(line);
	lexer(tokens, envp);
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

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	char	*buf;
	t_state	state;

	buf = ft_strdup("");
	state = STATE_GENERAL;
	while (*line)
	{
		if (state == STATE_GENERAL)
			state = handle_general(tokens, &buf, line);
		else if (state == STATE_SQUOTE || state == STATE_DQUOTE)
			handle_quote();
		line++;
	}
	if (ft_strlen(buf) > 0)
		add_token(&tokens, buf);
	else
		free(buf);
	return (tokens);
}
// >>> <<< how handle these?

void	lexer(t_token *head, t_env *envp)
{
	t_token	*cur;

	cur = head;
	while (cur)
	{
		if (cur->token_type == TOKEN_DQUOTE || cur->token_type == TOKEN_STRING)
			replace_env(cur, envp);
		if (cur->token_type == TOKEN_QUOTE || cur->token_type == TOKEN_DQUOTE)
			remove_quote(cur);
		cur = cur->next;
	}
}

t_ast_node	*make_ast(t_token *tokens)
{
	t_ast_node	*head;
	t_token		*ptr;

	ptr = tokens;
	head = parse_pipe(tokens, &ptr);
	return (head);
}
