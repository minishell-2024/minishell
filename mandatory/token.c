/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:05:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/21 22:34:07 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	add_token(t_token **token_addr, char *str)
{
	t_token	*new;
	t_token	*tokens;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (FAIL);
	new->word = str;
	new->token_type = get_tokentype(str);
	new->next = 0;
	if (!*token_addr)
	{
		*token_addr = new;
		return (SUCCESS);
	}
	tokens = *token_addr;
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

t_tokentype	get_tokentype(char *str)
{
	if (!str || !*str)
		return (TOKEN_END);
	if (ft_strncmp("|", str, ft_strlen(str)) == 0)
		return (TOKEN_PIPE);
	if (ft_strncmp("<<", str, ft_strlen(str)) == 0)
		return (TOKEN_DLESS);
	if (ft_strncmp(">>", str, ft_strlen(str)) == 0)
		return (TOKEN_DGREAT);
	if (ft_strncmp("<", str, ft_strlen(str)) == 0)
		return (TOKEN_LESS);
	if (ft_strncmp(">", str, ft_strlen(str)) == 0)
		return (TOKEN_GREAT);
	if (*str == '"')
		return (TOKEN_DQUOTE);
	if (*str == '\'')
		return (TOKEN_QUOTE);
	return (TOKEN_STRING);
}

int	delete_tokens(t_token **tokens)
{

}
