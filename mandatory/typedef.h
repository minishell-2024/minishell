/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 03:35:38 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/29 21:28:06 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef enum e_state
{
	STATE_GENERAL,
	STATE_SQUOTE,
	STATE_DQUOTE
}	t_state;

typedef enum e_tokentype
{
	TOKEN_END,
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_REDIRECT
}	t_tokentype;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_DELIMIT,
	REDIR_OUTPUT,
	REDIR_APPEND
}	t_redir_type;

typedef struct s_token
{
	char			*word;
	t_tokentype		type;
	struct s_token	*next;
}	t_token;

#endif