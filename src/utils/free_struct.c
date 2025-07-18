/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/18 11:46:04 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"


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
			safe_close(&exec->pipes[i][0]);
			safe_close(&exec->pipes[i][1]);
			free(exec->pipes[i]);
			exec->pipes[i] = NULL;
		}
		i++;
	}
	free(exec->pipes);
	exec->pipes = NULL;
}
