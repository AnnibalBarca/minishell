#include "parsing.h"

char	*process_question_mark_expansion(const char **str_ptr, char **envp,
		int *last_exit_status)
{
	(*str_ptr)++;
	return (get_env_var_value("?", envp, last_exit_status));
}

char	*process_accolades_expansion(const char **str_ptr)
{
	const char	*start;
	char		*var_name;

	(*str_ptr)++;
	start = *str_ptr;
	while (**str_ptr && **str_ptr != '}')
		(*str_ptr)++;
	if (**str_ptr == '}')
	{
		if (*str_ptr == start)
			var_name = ft_strdup("");
		else
			var_name = ft_substr(start, 0, *str_ptr - start);
		(*str_ptr)++;
	}
	else
	{
		var_name = ft_substr(start - 2, 0, *str_ptr - start + 2);
		return (ft_strdup("${"));
	}
	return (var_name);
}

char	*process_regular_variable_expansion(const char **str_ptr)
{
	t_str_builder	var_name_sb;
	char			*var_name;

	sb_init(&var_name_sb);
	while (is_valid_var_char(**str_ptr))
	{
		sb_append_char(&var_name_sb, **str_ptr);
		(*str_ptr)++;
	}
	var_name = sb_to_string_and_free(&var_name_sb);
	return (var_name);
}