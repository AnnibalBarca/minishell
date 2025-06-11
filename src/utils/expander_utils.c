/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:15:31 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/08 20:48:49 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/parsing.h"

char	*get_env_var_value(const char *var_name, char **envp,
		int last_exit_status)
{
	char	*value;

	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(last_exit_status));
	value = find_env_var(envp, var_name);
	if (value)
		return (ft_strdup(value));
	return (NULL);
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
