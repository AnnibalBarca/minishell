/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:15:31 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/26 15:56:21 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*get_env_var_value(const char *var_name, char **envp,
		int last_exit_status)
{
	int		i;
	size_t	name_len;

	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(last_exit_status));
	if (!envp)
		return (NULL);
	name_len = ft_strlen(var_name);
	if (name_len == 0)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, name_len) == 0
			&& envp[i][name_len] == '=')
		{
			return (ft_strdup(envp[i] + name_len + 1));
		}
		i++;
	}
	return (NULL);
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	handle_glob_matches(char **glob_matches, t_token **head, char **fields)
{
	int j;

	if (!glob_matches)
	{
		free_char_array(fields);
		free_token_list(*head);
		return (0);
	}
	j = 0;
	while (glob_matches[j])
	{
		if (!create_and_append_token(head, glob_matches[j], T_WORD, Q_NONE))
		{
			while (glob_matches[j])
				free(glob_matches[j++]);
			free(glob_matches);
			free_char_array(fields);
			free_token_list(*head);
			return (0);
		}
		glob_matches[j] = NULL;
		j++;
	}
	free(glob_matches);
	return (1);
}