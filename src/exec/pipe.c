/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:22:03 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/13 17:25:32 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	create_pipes(t_exec *exec)
{
	int	i;

	exec->cmd_count = find_size_cmd(exec->cmd_list);
	if (exec->cmd_count <= 1)
		return (0);
	exec->pipes = ft_calloc(exec->cmd_count - 1, sizeof(int *));
	if (!exec->pipes)
		return (-1);
		
	for (i = 0; i < exec->cmd_count - 1; i++)
	{
		exec->pipes[i] = ft_calloc(2, sizeof(int));
		if (!exec->pipes[i] || pipe(exec->pipes[i]) == -1)
		{
			exec_error(exec, 1, "minishell: pipe: %s\n", strerror(errno));
			return (-1);
		}
	}
	return (0);
}

void	close_all_pipes(t_exec *exec)
{
	int	i;

	if (!exec->pipes)
		return ;
	for (i = 0; i < exec->cmd_count - 1; i++)
	{
		if (exec->pipes[i])
		{
			if (exec->pipes[i][0] >= 0)
				close(exec->pipes[i][0]);
			if (exec->pipes[i][1] >= 0)
				close(exec->pipes[i][1]);
		}
	}
}
