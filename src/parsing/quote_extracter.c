/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_extracter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:36:09 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/14 11:13:58 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	extract_quoted_content(const char **line, char quote_char,
		t_str_builder *sb)
{
	(*line)++;
	while (**line && **line != quote_char)
	{
		if (!sb_append_char(sb, **line))
			return (0);
		(*line)++;
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
		sb_append_char(sb, **line);
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
