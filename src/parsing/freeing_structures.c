/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_structures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:38:02 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/30 20:36:53 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	cleanup_syntax_result(t_syntax_result *result)
{
	if (!result)
		return ;
	if (result->tokens)
	{
		free_token_list(result->tokens);
		result->tokens = NULL;
	}
	if (result->error_token)
	{
		free(result->error_token);
		result->error_token = NULL;
	}
}
void	cleanup_parsing_context(char **line, t_token **tokens,
		t_syntax_result *result)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (tokens && *tokens)
	{
		free_token_list(*tokens);
		*tokens = NULL;
	}
	if (result)
		cleanup_syntax_result(result);
}

int	safe_cleanup_and_return_null(char **line, t_token **tokens,
		t_syntax_result *result, char ***accumulated_input)
{
	cleanup_parsing_context(line, tokens, result);
	if (accumulated_input)
		*accumulated_input = NULL;
	return (0);
}
