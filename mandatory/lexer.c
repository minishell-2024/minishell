/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:00:05 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 13:31:51 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(char *line)
{
	int	idx;

	idx = 0;
	while (!isspace(line[idx]))
		idx++;
	return (ft_substr(line, 0, idx));
}

void	replace_env(t_token *token, t_env *envp)
{
	char	*dollar_pos;
	char	*name;
	char	*val;
	char	*new;

	dollar_pos = ft_strchr(token->word, '$');
	while (dollar_pos)
	{
		name = read_word(dollar_pos + 1);
		val = 0;
		while (envp)
		{
			if (envp->name == name)
			{
				val = envp->value;
				break ;
			}
			envp = envp->next;
		}
		new = insert_env(token->word, val, ft_strlen(name));
		free(token->word);
		free(name);
		token->word = new;
		dollar_pos = ft_strchr(dollar_pos + 1, '$');
	}
}

char	*insert_env(char *origin, char *val, int name_size)
{
	char	*new_word;
	int		new_size;
	char	*idx;

	new_size = ft_strlen(origin) - name_size + ft_strlen(val);
	new_word = (char *)malloc(sizeof(char) * new_size);
	if (!new_word)
		return (FAIL);
	idx = new_word;
	while (*origin != '$')
	{
		*idx = *origin;
		idx++;
		origin++;
	}
	idx = ft_memcpy(idx, val, ft_strlen(val)) + ft_strlen(val);
	origin += name_size + 1;
	while (*origin)
	{
		*idx = *origin;
		idx++;
		origin++;
	}
	*idx = 0;
	return (new_word);
}
