/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/08 22:08:14 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "signals.h"

extern int	g_signal_test;

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_token *tokens;
	char **env_copy;
	int exit_status;

	(void)argc;
	(void)argv;
	init_signal_handling();
	setup_interactive_signals();
	env_copy = copy_env_array(envp);
	if (!env_copy)
		return (EXIT_FAILURE);
	while (1)
	{
		input = readline("\033[1;32mminishell$\033[0m ");
		if (!input)
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = parse_complete_input(&input, env_copy, g_signal_test);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		exit_status = pipex(tokens, &env_copy);
		g_signal_test = exit_status;
		free_token_list(tokens);
		free(input);
	}
	ft_freesplit(env_copy);
	return (g_signal_test);
}