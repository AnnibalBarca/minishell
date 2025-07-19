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
	rl_done = 1;
	//rl_redisplay();
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_test = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	g_signal_test = 131;
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit_child(int sig)
{
	(void)sig;
	g_signal_test = 131;
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	g_signal_test = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	handle_sigint_noninteractive(int sig)
{
	(void)sig;
	g_signal_test = 130;
}

static void	handle_sigquit_noninteractive(int sig)
{
	(void)sig;
	g_signal_test = 131;
}

void	setup_interactive_signals(void)
{
	setup_signal(SIGINT, handle_sigint);
	setup_signal(SIGQUIT, handle_sigquit);
}

void	setup_noninteractive_signals(void)
{
	setup_signal(SIGINT, handle_sigint_noninteractive);
	setup_signal(SIGQUIT, handle_sigquit_noninteractive);
}
