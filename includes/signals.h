/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:42:53 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/13 22:42:28 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "struct.h"

extern int	g_signal_test;
extern pid_t	g_foreground_pid;

void		handle_sigint_heredoc(int sig);
void		setup_interactive_signals(void);
void		setup_child_signals(void);
void		setup_heredoc_signals(void);
void		reset_signals(void);
void		setup_parent_signals(void);
void		setup_noninteractive_signals(void);
void		init_signal_handling(void);
void		set_foreground_process_group(pid_t pid);
void		restore_shell_process_group(void);

#endif