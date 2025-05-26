/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_state_machine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:38:32 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/26 17:27:12 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_syntax_result	analyze_syntax(t_token *tokens)
{
	t_syntax_result result;
	t_parser_context ctx;

	result.status = PARSE_OK;
	result.next_prompt = PROMPT_MAIN;
	result.error_token = NULL;
	result.tokens = tokens;
	init_parser_context(&ctx, tokens, &result);

	while (ctx.current && result.status == PARSE_OK)
	{
		if (!process_current_token(&ctx))
			break ;
		ctx.current = ctx.current->next;
	}

	return (result);
}