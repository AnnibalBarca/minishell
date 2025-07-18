/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/16 12:44:24 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "signals.h"

int			g_signal_received = 0;

static int	initialize_shell(char **envp, char ***env_copy)
{
	setup_interactive_signals();
	*env_copy = copy_env_array(envp);
	if (!*env_copy)
		return (0);
	return (1);
}

static int	handle_empty_or_null_input(char **input)
{
	if (!*input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (1);
	}
	if (**input == '\0')
	{
		free(*input);
		return (2);
	}
	return (0);
}

static int	handle_signal_interruption(int *exit_status, char **input)
{
	if (g_signal_received == 130)
	{
		*exit_status = 130;
		g_signal_received = 0;
		free(*input);
		return (1);
	}
	return (0);
}

static int	process_command(char **input, char **env_copy, int *exit_status)
{
	t_token	*tokens;
	int		command_exit_status;

	tokens = parse_complete_input(input, env_copy, *exit_status);
	if (!tokens)
	{
		*exit_status = 2;
		return (0);
	}
	command_exit_status = pipex(tokens, &env_copy);
	if (g_signal_received == 130)
	{
		*exit_status = 130;
		g_signal_received = 0;
	}
	else if (g_signal_received == 131)
	{
		*exit_status = 131;
		g_signal_received = 0;
	}
	else
		*exit_status = command_exit_status;
	free_token_list(tokens);
	return (1);
}

static void	shell_loop(char **env_copy, int *exit_status)
{
	char	*input;
	int		input_status;

	while (1)
	{
		input = readline("\033[1;32mminishell$\033[0m ");
		input_status = handle_empty_or_null_input(&input);
		if (input_status == 1)
			break ;
		if (input_status == 2)
			continue ;
		if (handle_signal_interruption(exit_status, &input))
			continue ;
		add_history(input);
		process_command(&input, env_copy, exit_status);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char **env_copy;
	int exit_status;

	(void)argc;
	(void)argv;
	if (!initialize_shell(envp, &env_copy))
		return (EXIT_FAILURE);
	exit_status = 0;
	shell_loop(env_copy, &exit_status);
	ft_freesplit(env_copy);
	return (exit_status);
}