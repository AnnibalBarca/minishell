/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:42:41 by Mimoulapino       #+#    #+#             */
/*   Updated: 2025/04/12 12:44:44 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

// Supprime les quotes tout en respectant les règles de bash
// - Quotes simples : tout est littéral
// - Quotes doubles : $ est laissé tel quel (sera expand plus tard)
char	*remove_quotes(const char *src)
{
	char	*dst;
	int		i;
	int		j;
	char	quote;

	dst = malloc(ft_strlen(src) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (!quote && is_quote(src[i]))
		{
			quote = src[i];
			i++;
			continue ;
		}
		else if (quote && src[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dst);
}

// Fonction à appeler après la tokenization pour nettoyer les quotes
void	process_quotes(t_token *tokens)
{
	char *cleaned;

	while (tokens)
	{
		if (tokens->type == T_WORD)
		{
			cleaned = remove_quotes(tokens->value);
			free(tokens->value);
			tokens->value = cleaned;
		}
		tokens = tokens->next;
	}
}