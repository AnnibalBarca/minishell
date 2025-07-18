/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by Mimoulapino      #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

int		g_signal_test = 0;

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal_test = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit(130);
}

static void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_signal_test = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_noninteractive(int sig)
{
	(void)sig;
	g_signal_test = 130;
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, handle_sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_noninteractive_signals(void)
{
	signal(SIGINT, handle_sigint_noninteractive);
	signal(SIGQUIT, SIG_IGN);
}
