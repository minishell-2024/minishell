/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:04:28 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/22 21:21:25 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line, t_env *envp)
{
	t_token	*tokens;
	int		length;

	if (!line || !ft_strlen(line))
		return (FAIL);
	if (check_quote(line) == FAIL)
		return (QUOTE_INCOMPLETE);
	tokens = 0;
	while (*line)
	{
		while (isspace(*line))
			line++;
		length = tokenize(line, tokens);
		if (!length)
			return (FAIL);
		line += length;
	}
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

int	tokenize(char *line, t_token *tokens)
{
	char	*str;

	if (*line == '|')
		str = ft_strdup("|");
	else if (*line == '<')
	{
		if (*(line + 1) == '<')
			str = ft_strdup("<<");
		else
			str = ft_strdup("<");
	}
	else if (*line == '>')
	{
		if (*(line + 1) == '>')
			str = ft_strdup(">>");
		else
			str = ft_strdup(">");
	}
	else if (*line == '\'' || *line == '"')
		str = read_string(line);
	else
		str = read_word(line);
	if (!add_token(&tokens, str))
		return (delete_tokens(&tokens));
	return (ft_strlen(str));
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

void	make_ast(t_token *tokens)
{
	t_ast_node	*head;
	t_token		*ptr;

	ptr = tokens;
	head = parse_pipe(tokens, &ptr);
}