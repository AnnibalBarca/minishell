/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:03:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/15 19:21:27 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_one(t_exec *exec, char **envp)
{
	exec->pids[0] = fork();
	if (exec->pids[0] == -1)
		free_pipex(exec, 1, "pid", strerror(errno));
	if (exec->pids[0] == 0)
	{
		if (exec->infile_name != NULL)
		{
			if (dup2(exec->infile, STDIN_FILENO) == -1)
				free_pipex(exec, 1, "dup2", strerror(errno));
		}
		if (exec->outfile_name != NULL)
		{
			if (dup2(exec->outfile, STDOUT_FILENO) == -1)
				free_pipex(exec, 1, "caca", strerror(errno));
		}
		close(exec->outfile);
		close(exec->infile);
		execute_bonus(exec, argv, envp);
	}
}
