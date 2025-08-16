/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:11:15 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/16 12:52:33 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*expand_tokens(t_token *tokens, char **envp, int *exit_status)
{
	t_token				*current;
	t_token				*expanded_head;
	t_token				*prev;
	t_expand_context	ctx;

	ctx.envp = envp;
	ctx.exit_status = *exit_status;
	expanded_head = NULL;
	current = tokens;
	prev = NULL;
	while (current)
	{
		if (!process_single_token(current, prev, &expanded_head, &ctx))
			return (free_token_list_and_return_null(expanded_head));
		prev = current;
		current = current->next;
	}
	return (expanded_head);
}
