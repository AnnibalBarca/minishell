
#include "parsing.h"
#include "utils.h"

int	token_has_quotes(const char *token_value)
{
	if (!token_value)
		return (0);
	while (*token_value)
	{
		if (*token_value == '\'' || *token_value == '"')
			return (1);
		token_value++;
	}
	return (0);
}

int	token_is_fully_quoted(const char *token_value)
{
	int	len;

	if (!token_value)
		return (0);
	len = ft_strlen(token_value);
	if (len < 2)
		return (0);
	if ((token_value[0] == '\'' && token_value[len - 1] == '\'')
		|| (token_value[0] == '"' && token_value[len - 1] == '"'))
		return (1);
	return (0);
}

int	should_field_split(const char *token_value)
{
	int	in_single_quote;
	int	in_double_quote;

	if (!token_value)
		return (1);
	in_single_quote = 0;
	in_double_quote = 0;
	while (*token_value)
	{
		if (*token_value == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*token_value == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote)
			return (1);
		token_value++;
	}
	return (0);
}