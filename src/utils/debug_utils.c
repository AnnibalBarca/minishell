/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:30:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/16 12:50:11 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/struct.h"
#include <stdio.h>

static const char	*get_token_type_name(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == T_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == T_APPEND)
		return ("APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	print_token(const t_token *token, int index)
{
	if (!token)
	{
		printf("[token %d] NULL\n", index);
		return ;
	}
	printf("[token %d] type: %s, value: '%s'\n",
		index,
		get_token_type_name(token->type),
		token->value ? token->value : "(null)");
}

void	print_token_list(const t_token *head)
{
	const t_token	*current;
	int				index;

	if (!head)
	{
		printf("Token list is empty\n");
		return ;
	}
	current = head;
	index = 0;
	while (current)
	{
		print_token(current, index);
		current = current->next;
		index++;
	}
}

void	print_str_builder(const t_str_builder *sb)
{
	if (!sb)
	{
		printf("[str_builder: NULL]\n");
		return ;
	}
	printf("[str_builder] len: %zu, cap: %zu, str: '%s'\n",
		sb->len, sb->capacity, sb->str ? sb->str : "(null)");
}
