/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:00:05 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/21 20:31:55 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env(t_token *token, t_env *envp)
{
	char	*loc;
	char	*key;
	char	*val;
	char	*new;

	loc = ft_strchr(token->word, '$');
	if (loc == 0)
		return ;
	key = read_word(loc + 1);
	val = 0;
	while (envp)
	{
		if (envp->name == key)
		{
			val = envp->value;
			break ;
		}
		envp = envp->next;
	}
	new = insert_env(token->word, key, val);
	free(token->word);
	free(key);
	token->word = new;
}

void	remove_quote(t_token *token)
{

}

char	*insert_env(char *orgn, char *key, char *val)
{
	char	*env_str;
	int		new_length;
	char	*idx;

	new_length = ft_strlen(orgn) - ft_strlen(key) + ft_strlen(val);
	env_str = (char *)malloc(sizeof(char) * new_length);
	if (!env_str)
		return (FAIL);
	idx = env_str;
	while (*orgn != '$')
	{
		*idx = *orgn;
		idx++;
		orgn++;
	}
	ft_memcpy(idx, val, ft_strlen(val));
	idx += ft_strlen(val);
	orgn += ft_strlen(key) + 1;
	while (*orgn)
	{
		*idx = *orgn;
		idx++;
		orgn++;
	}
	return (env_str);
}
