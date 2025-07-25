/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stripper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:49:12 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/24 14:34:47 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int	process_heredoc_char(t_str_builder *sb, const char **ip,
		char **envp, char *current_quote)
{
	if (!*current_quote && (**ip == '\'' || **ip == '"'))
	{
		*current_quote = **ip;
		if (!sb_append_char(sb, **ip))
			return (0);
		(*ip)++;
	}
	else if (*current_quote && **ip == *current_quote)
	{
		if (!sb_append_char(sb, **ip))
			return (0);
		*current_quote = 0;
		(*ip)++;
	}
	else if (*current_quote == '\'')
	{
		if (!sb_append_char(sb, **ip))
			return (0);
		(*ip)++;
	}
	else if (*current_quote == '"' && **ip == '\\' && (*(*ip + 1) == '$'
			|| *(*ip + 1) == '"' || *(*ip + 1) == '\\' || *(*ip + 1) == '\n'))
	{
		(*ip)++;
		if (!sb_append_char(sb, **ip))
			return (0);
		(*ip)++;
	}
	else if (should_expand_variable(**ip, *(*ip + 1), Q_DOUBLE))
	{
		if (!process_expansion(sb, ip, envp, 0))
			return (0);
	}
	else if (should_expand_variable(**ip, *(*ip + 1), Q_NONE))
	{
		if (!process_expansion(sb, ip, envp, 0))
			return (0);
	}
	else
	{
		if (!sb_append_char(sb, **ip))
			return (0);
		(*ip)++;
	}
	return (1);
}

char	*expand_heredoc_line(const char *line, char **envp)
{
	t_str_builder	sb;
	const char		*ip;
	char			current_quote;

	if (!line)
		return (NULL);
	sb_init(&sb);
	ip = line;
	current_quote = 0;
	while (*ip)
	{
		if (!process_heredoc_char(&sb, &ip, envp, &current_quote))
			return (sb_free_and_return_null(&sb));
	}
	return (sb_to_string_and_free(&sb));
}
