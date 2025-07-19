/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:08:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/19 13:54:46 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	should_expand_variable(char current_char, char next_char,
		t_quote quote_type)
{
	if (current_char != '$')
		return (0);
	if (quote_type == Q_SINGLE)
	{
		return (0);
	}
	if (is_valid_var_char(next_char) || next_char == '?' || next_char == '{')
	{
		return (1);
	}
	return (0);
}

static int	process_regular_char(t_str_builder *sb, const char **ip)
{
	if (!sb_append_char(sb, **ip))
		return (0);
	(*ip)++;
	return (1);
}

char	*expand_variables_in_str(const char *input_str, t_quote quote_type,
		char **envp, int last_exit_status)
{
	t_str_builder	sb;
	const char		*ip;
	char			*result;

	if (!input_str)
		return (NULL);
	sb_init(&sb);
	ip = input_str;
	while (*ip)
	{
		if (should_expand_variable(*ip, *(ip + 1), quote_type))
		{
			if (!process_expansion(&sb, &ip, envp, last_exit_status))
				return (sb_free_and_return_null(&sb));
		}
		else
		{
			if (!process_regular_char(&sb, &ip))
				return (sb_free_and_return_null(&sb));
		}
	}
	result = sb_to_string_and_free(&sb);
	return (result);
}
