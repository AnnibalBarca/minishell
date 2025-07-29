/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:56:30 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/29 17:27:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_numeric_string(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (sign == -1 && result == 922337203685477580LL && str[i] == '8')
		{
			result = 9223372036854775808ULL;
			i++;
			break ;
		}
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (sign == -1 && (unsigned long long)result > 9223372036854775808ULL)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_exec *exec, int parent)
{
	int		exit_code;
	t_args	*first_arg;
	t_args	*second_arg;

	if (!exec->cmd_list->args)
	{
		ft_putstr_fd("exit\n", 2);
		if (parent)
		{
			if (exec->envp_exists == 1 && exec->envp)
			{
				free_split(exec->envp);
				exec->envp = NULL;
			}
			free_parent(exec, 0, NULL, NULL);
		}
		else
			free_child(exec, 0, NULL, NULL);
	}
	first_arg = exec->cmd_list->args->next;
	if (!first_arg)
	{
		ft_putstr_fd("exit\n", 2);
		if (parent)
		{
			if (exec->envp_exists == 1 && exec->envp)
			{
				free_split(exec->envp);
				exec->envp = NULL;
			}
			free_parent(exec, 0, NULL, NULL);
		}
		else
			free_child(exec, 0, NULL, NULL);
	}
	second_arg = first_arg->next;
	if (second_arg)
	{
		if (!is_numeric_string(first_arg->cmd_args))
		{
			ft_putstr_fd("exit\n", 2);
			ft_message("exit", first_arg->cmd_args,
				"numeric argument required");
			if (parent)
			{
				if (exec->envp_exists == 1 && exec->envp)
				{
					free_split(exec->envp);
					exec->envp = NULL;
				}
				free_parent(exec, 255, NULL, NULL);
			}
			else
				free_child(exec, 255, NULL, NULL);
		}
		ft_putstr_fd("exit\n", 2);
		ft_message("exit", NULL, "too many arguments");
		return (1);
	}
	if (!is_numeric_string(first_arg->cmd_args))
	{
		ft_putstr_fd("exit\n", 2);
		ft_message("exit", first_arg->cmd_args, "numeric argument required");
		if (parent)
		{
			if (exec->envp_exists == 1 && exec->envp)
			{
				free_split(exec->envp);
				exec->envp = NULL;
			}
			free_parent(exec, 2, NULL, NULL);
		}
		else
			free_child(exec, 2, NULL, NULL);
	}
	exit_code = ft_atoi(first_arg->cmd_args);
	ft_putstr_fd("exit\n", 2);
	if (parent)
	{
		if (exec->envp_exists == 1 && exec->envp)
		{
			free_split(exec->envp);
			exec->envp = NULL;
		}
		free_parent(exec, (unsigned char)exit_code, NULL, NULL);
	}
	else
		free_child(exec, (unsigned char)exit_code, NULL, NULL);
	return ((unsigned char)exit_code);
}
