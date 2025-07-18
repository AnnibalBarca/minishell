/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/14 09:08:00 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	close_pipe_fd(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_all_pipes(t_exec *exec)
{
	int	i;

	if (!exec || !exec->pipes)
		return ;
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		if (exec->pipes[i])
		{
			close_pipe_fd(&exec->pipes[i][0]);
			close_pipe_fd(&exec->pipes[i][1]);
			free(exec->pipes[i]);
			exec->pipes[i] = NULL;
		}
		i++;
	}
	free(exec->pipes);
	exec->pipes = NULL;
}
