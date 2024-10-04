/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:00:05 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/05 04:14:25 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		available_char(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (SUCCESS);
	return (FAIL);
}

char	*read_word(char *line)
{
	char	*word;
	int		idx;

	idx = 0;
	while (line[idx])
	{
		if (!available_char(line[idx]))
			break ;
		if (idx == 0 && line[idx] == '?')
		{
			idx++;
			break ;
		}
		idx++;
	}
	word = ft_substr(line, 0, idx);
	if (!word)
		common_error("malloc", 0, 0, 0);
	return (word);
}

char	*key_to_value(char *word, t_line *input)
{
	char	*dollar_pos;
	char	*name;
	t_env	*right_env;
	char	*value;
	char	*old_buf;

	dollar_pos = ft_strchr(word, '$');
	while (dollar_pos)
	{
		value = 0;
		name = read_word(dollar_pos + 1);
		if (!name)
			common_error("malloc", 0, 0, 0);
		right_env = find_env(input, name);
		if (right_env)
			value = right_env->value;
		old_buf = word;
		word = insert_value(word, value, ft_strlen(name));
		free(name);
		free(old_buf);
		dollar_pos = ft_strchr(word, '$');
	}
	return (word);
}

char	*insert_value(char *origin, char *val, int name_size)
{
	char	*new_word;
	int		new_size;
	char	*idx;

	new_size = ft_strlen(origin) - name_size + ft_strlen(val);
	new_word = (char *)ft_calloc(sizeof(char), new_size);
	if (!new_word)
		common_error("malloc", 0, 0, 0);
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
