/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by Mimoulapino      #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	init_signal_handling(void)
{
	pid_t	shell_pgid;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		shell_pgid = getpgrp();
		if (tcgetpgrp(STDIN_FILENO) != shell_pgid)
			tcsetpgrp(STDIN_FILENO, shell_pgid);
	}
}

void	set_foreground_process_group(pid_t pid)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && pid > 0)
	{
		g_foreground_pid = pid;
		if (tcgetpgrp(STDIN_FILENO) == getpgrp())
		{
			if (setpgid(pid, pid) == 0)
				tcsetpgrp(STDIN_FILENO, pid);
		}
	}
}

void	restore_shell_process_group(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		if (tcgetpgrp(STDIN_FILENO) != getpgrp())
			tcsetpgrp(STDIN_FILENO, getpgrp());
		g_foreground_pid = 0;
	}
}
