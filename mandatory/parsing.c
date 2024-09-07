/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:04:28 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/07 22:46:53 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line)
{
	t_token	*tokens;

	if (!line || !ft_strlen(line))
		return (0);
	if (check_quote(line) == FAIL)
		return (QUOTE_INCOMPLETE); //newline 으로 입력 다시 받아야 함.
	if (tokenize(line, tokens) == FAIL)
		return (FAIL);
	expand_env(tokens);
	make_tree(tokens);
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
	int	idx;

	idx = 0;
	while (line[idx])
	{
		while (ft_isspace(line[idx]))
			idx++;
		//get command and add to tokens
		if (line[idx] == '\'')
		;
		else if (line[idx] == '"')
		;
		else if (isprint(line[idx]))
		;
	}
}
