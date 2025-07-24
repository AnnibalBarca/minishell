/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:36:09 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/24 14:35:29 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	extract_quoted_content(const char **line, char quote_char,
		t_str_builder *sb)
{
	(*line)++;
	while (**line && **line != quote_char)
	{
		if (quote_char == '"' && **line == '\\' && (*(*line + 1) == '$'
				|| *(*line + 1) == '"' || *(*line + 1) == '\\' || *(*line
					+ 1) == '\n'))
		{
			(*line)++;
			if (!sb_append_char(sb, **line))
				return (0);
			(*line)++;
		}
		else
		{
			if (!sb_append_char(sb, **line))
				return (0);
			(*line)++;
		}
	}
	if (**line == quote_char)
		(*line)++;
	return (1);
}

int	extract_unquoted_content(const char **line, t_str_builder *sb)
{
	while (**line && is_word_char(**line) && !is_operator_start(**line)
		&& **line != '\'' && **line != '"')
	{
		if (**line == '\\' && *(*line + 1))
		{
			(*line)++;
			sb_append_char(sb, **line);
		}
		else
		{
			sb_append_char(sb, **line);
		}
		(*line)++;
	}
	return (1);
}

static int	process_quoted_section(const char **line, char quote_char)
{
	(*line)++;
	while (**line && **line != quote_char)
		(*line)++;
	if (**line == quote_char)
	{
		(*line)++;
		return (1);
	}
	return (0);
}

int	has_unclosed_quotes(const char *line)
{
	while (line && *line)
	{
		if (*line == '\'' || *line == '"')
		{
			if (!process_quoted_section(&line, *line))
				return (1);
		}
		else
			line++;
	}
	return (0);
}
