/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:11:15 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/18 11:21:41 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*expand_token_value(const char *value, t_quote quote_type, char **envp,
		int exit_status)
{
	if (quote_type == Q_SINGLE)
		return (ft_strdup(value));
	if (quote_type == Q_MIXED && ft_strchr(value, '='))
		return (ft_strdup(value));
	if (quote_type)
	return (expand_variables_in_str(value, quote_type, envp, exit_status));
}

int	should_field_split(t_quote quote_type)
{
	return (quote_type == Q_NONE);
}

t_token	*expand_tokens(t_token *tokens, char **envp, int exit_status)
{
	t_token	*current;
	t_token	*expanded_head;
	char	*op_copy;

	expanded_head = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == T_WORD)
		{
			if (!process_word_expansion(current, &expanded_head, envp,
					exit_status))
				return (free_token_list_and_return_null(expanded_head));
		}
		else
		{
			op_copy = ft_strdup(current->value);
			if (!op_copy || !create_and_append_token(&expanded_head, op_copy,
					current->type, Q_NONE))
				return (free_token_list_and_return_null(expanded_head));
		}
		current = current->next;
	}
	return (expanded_head);
}
