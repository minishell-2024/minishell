/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:27:08 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 19:18:24 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	env_len(t_line *line)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = line->env;
	while (temp)
	{
		i++;
		temp = temp->env_next;
	}
	return (i);
}

int	is_identifier(char *str)
{
	const int length = ft_strlen(str);
	int 				i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (0);
	while (++i < length)
	{
		if (str[i] != '_' && !ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
