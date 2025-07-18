/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:31:48 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/18 09:48:12 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*process_complete_syntax(t_syntax_result syntax_result, char **envp,
		int exit_status)
{
	t_token	*expanded_tokens;

	expanded_tokens = expand_tokens(syntax_result.tokens, envp, exit_status);
	free_token_list(syntax_result.tokens);
	syntax_result.tokens = NULL;
	return (expanded_tokens);
}

static int	check_signal_interruption(void)
{
	if (g_signal_test == 130)
	{
		g_signal_test = 130;
		return (1);
	}
	return (0);
}

static t_token	*handle_initial_checks(char **line, char ***accumulated_input)
{
	if (check_signal_interruption())
		return (cleanup_parsing_and_return_null(line, accumulated_input, NULL,
				NULL));
	if (has_unclosed_quotes(*line))
		return (cleanup_parsing_and_return_null(line, accumulated_input, NULL,
				"minishell: syntax error: unclosed quotes\n"));
	return ((t_token *)1);
}

static t_token	*handle_syntax_processing(t_syntax_result *syntax_result,
		char **line, char ***accumulated_input, char **envp, int exit_status)
{
	if (syntax_result->status == PARSE_OK)
	{
		**accumulated_input = *line;
		if (handle_syntax_success(syntax_result, envp,
				exit_status) == PARSE_SUCCESS)
			return (syntax_result->expanded_tokens);
		return (cleanup_parsing_and_return_null(line, accumulated_input,
				syntax_result, NULL));
	}
	else
	{
		handle_syntax_error(syntax_result);
		return (cleanup_parsing_and_return_null(line, accumulated_input,
				syntax_result, NULL));
	}
}

t_token	*parse_complete_input(char **accumulated_input, char **envp,
		int exit_status)
{
	char			*line;
	t_token			*tokens;
	t_syntax_result	syntax_result;
	t_token			*check_result;

	line = *accumulated_input;
	check_result = handle_initial_checks(&line, &accumulated_input);
	if (check_result != (t_token *)1)
		return (check_result);
	tokens = lexer(line);
	if (!tokens)
		return (cleanup_parsing_and_return_null(&line, &accumulated_input, NULL,
				NULL));
	syntax_result = analyze_syntax(tokens);
	return (handle_syntax_processing(&syntax_result, &line, &accumulated_input,
			envp, exit_status));
}
