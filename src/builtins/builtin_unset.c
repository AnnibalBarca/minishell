/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:55:14 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/23 15:35:22 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	remove_env_var_return(char ***env_ptr, char *name)
{
	int	index;
	int	i;

	if (!env_ptr || !*env_ptr || !name)
		return (0);
	index = find_env_index(*env_ptr, name);
	if (index == -1)
		return (0);
	free((*env_ptr)[index]);
	i = index;
	while ((*env_ptr)[i + 1])
	{
		(*env_ptr)[i] = (*env_ptr)[i + 1];
		i++;
	}
	(*env_ptr)[i] = NULL;
	return (1);
}

int	builtin_unset(t_args *args, char ***env_ptr)
{
	int		exit_status;
	int		result;
	t_args	*current;

	if (!args || !env_ptr || !*env_ptr)
		return (0);
	exit_status = 0;
	current = args->next;
	while (current)
	{
		if (!is_valid_var_name(current->cmd_args))
			exit_status = 1;
		else
		{
			result = remove_env_var_return(env_ptr, current->cmd_args);
			if (result == -1)
				exit_status = 1;
		}
		current = current->next;
	}
	return (exit_status);
}
