/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:04:28 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/13 20:36:06 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line)
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
		line += length;
	}
	make_ast(tokens);
	//open pipes?
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

char	*read_string(char *line)
{
	int		quote_idx;
	int		c;

	c = *line % 256;
	quote_idx = 1;
	while (line[quote_idx] != c)
		quote_idx++;
	quote_idx++;
	while (!isspace(line[quote_idx]))
		quote_idx++;
	return (ft_substr(line, 0, quote_idx));
}

char	*read_word(char *line)
{
	int	idx;

	idx = 0;
	while (!isspace(line[idx]))
		idx++;
	return (ft_substr(line, 0, idx));
}
