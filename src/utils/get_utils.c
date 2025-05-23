/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:01:32 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/23 18:42:28 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

size_t	get_size(char *str)
{
	size_t	k;
	size_t	i;
	char	tmp;

	i = 0;
	k = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] && str[i + 1] != '\'')
			|| (str[i] == '\"' && str[i + 1] && str[i + 1] != '\"'))
		{
			tmp = str[i];
			i++;
			while (str[i] && str[i + 1] && str[i] != tmp)
				i++;
			k += 2;
		}
		else if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '\"' && str[i + 1] == '\"'))
			i++;
		i++;
	}
	return (i - k);
}

char	*get_string(char *s, size_t i, size_t k, size_t size)
{
	char	*ptr;
	char	tmp;

	ptr = malloc(sizeof(char) * (size + 1));
	while (k < size)
	{
		while ((s[i] == '\'' && s[i + 1] && s[i + 1] != '\'')
			|| (s[i] == '\"' && s[i + 1] && s[i + 1] != '\"'))
		{
			tmp = s[i++];
			while (s[i] && s[i + 1] && s[i] != tmp)
				ptr[k++] = s[i++];
			i++;
		}
		if (k == size)
			break ;
		if ((s[i] == '\'' && s[i + 1] == '\'')
			|| (s[i] == '\"' && s[i + 1] == '\"'))
			ptr[k++] = s[i++];
		ptr[k++] = s[i++];
	}
	ptr[k] = '\0';
	free(s);
	return (ptr);
}

// void	remove_quotes(t_cmd *lst)
// {
// 	int		i;

// 	while (lst)
// 	{
// 		i = 0;
// 		while (lst->cmd[i])
// 		{
// 			if (lst->cmd[i] != NULL
// 				&& get_size(lst->cmd[i]) != ft_strlen(lst->cmd[i]))
// 			{
// 				lst->cmd[i] = get_string(lst->cmd[i], 0, 0,
// 						get_size(lst->cmd[i]));
// 			}
// 			i++;
// 		}
// 		lst = lst->next;
// 	}
// }