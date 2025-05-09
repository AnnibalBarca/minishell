/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:03:03 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/09 16:49:25 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	pipex_init(t_exec *exec, char **envp)
{
	size_t	i;

	exec->pipex = (t_pipex){0};
	exec->pipex.infile = -1;
	exec->pipex.outfile = -1;
	exec->pipex.here_doc = 1;
	exec->pipex.i = -1;
	exec->pipex.i_wait = -1;
	exec->pipex.envp = 1;
	i = 0;
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp || !envp[i])
	{
		exec->pipex.envp = 0;
		return ;
	}
	exec->pipex.paths = ft_split(envp[i] + 5, ':');
	if (!exec->pipex.paths)
		if (errno == ENOMEM)
			free_pipex(exec, -1, "malloc", strerror(errno));
}
