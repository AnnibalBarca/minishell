/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:41:55 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/05 17:44:03 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

int	g_exit_status = 0;

static void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_exit_status = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_child(int sig)
{
	(void)sig;
	g_exit_status = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	handle_sigquit_child(int sig)
{
	(void)sig;
	g_exit_status = 131;
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, handle_sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, handle_sigquit_child);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
