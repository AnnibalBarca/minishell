/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:39:08 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/26 15:55:09 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	free_token_list(t_token *list)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = list;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		free(current_token->value);
		free(current_token);
		current_token = next_token;
	}
}

int	create_and_append_token(t_token **head, char *value, t_token_type type,
		t_quote quote_status)
{
	t_token	*new_token;
	t_token	*current;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		free(value);
		return (0);
	}
	new_token->value = value;
	new_token->type = type;
	new_token->quote = quote_status;
	new_token->next = NULL;
	if (*head == NULL)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
	return (1);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_word_char(char c)
{
	if (is_whitespace(c) || c == '|' || c == '<' || c == '>' || c == '\0')
		return (0);
	return (1);
}

int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*create_pipe_token(void)
{
	return (ft_strdup("|"));
}

char	*create_heredoc_token(void)
{
	return (ft_strdup("<<"));
}

char	*create_redirect_in_token(void)
{
	return (ft_strdup("<"));
}

char	*create_append_token(void)
{
	return (ft_strdup(">>"));
}

char	*create_redirect_out_token(void)
{
	return (ft_strdup(">"));
}

int	handle_pipe_operator(const char **line, t_token **head)
{
	char	*op_val;

	op_val = create_pipe_token();
	if (!op_val)
		return (0);
	(*line)++;
	return (create_and_append_token(head, op_val, T_PIPE, Q_NONE));
}

int	handle_less_operator(const char **line, t_token **head)
{
	char			*op_val;
	t_token_type	type;

	if (*(*line + 1) == '<')
	{
		op_val = create_heredoc_token();
		type = T_HEREDOC;
		*line += 2;
	}
	else
	{
		op_val = create_redirect_in_token();
		type = T_REDIRECT_IN;
		(*line)++;
	}
	if (!op_val)
		return (0);
	return (create_and_append_token(head, op_val, type, Q_NONE));
}

int	handle_greater_operator(const char **line, t_token **head)
{
	char			*op_val;
	t_token_type	type;

	if (*(*line + 1) == '>')
	{
		op_val = create_append_token();
		type = T_APPEND;
		*line += 2;
	}
	else
	{
		op_val = create_redirect_out_token();
		type = T_REDIRECT_OUT;
		(*line)++;
	}
	if (!op_val)
		return (0);
	return (create_and_append_token(head, op_val, type, Q_NONE));
}

int	cleanup_and_return_zero(t_token **head)
{
	free_token_list(*head);
	*head = NULL;
	return (0);
}