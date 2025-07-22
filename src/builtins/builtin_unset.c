/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:55:14 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/22 10:32:39 by nagaudey         ###   ########.fr       */
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
	int		any_unset;
	int		result;
	t_args	*current;

	if (!args || !env_ptr || !*env_ptr)
		return (0);
	exit_status = 0;
	any_unset = 0;
	current = args->next;
	while (current)
	{
		if (!is_valid_var_name(current->cmd_args))
		{
			// ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			// ft_putstr_fd(current->cmd_args, STDERR_FILENO);
			// ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else
		{
			result = remove_env_var_return(env_ptr, current->cmd_args);
			if (result == 1)
				any_unset = 1;
			else if (result == -1)
				exit_status = 1;
		}
		current = current->next;
	}
	if (any_unset)
		return (0);
	return (exit_status);
}
