/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/15 19:20:42 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1>"
		"<...> <file>\n", 1);
	return (-1);
}

int	pipex(t_exec *exec, char **envp)
{
	t_exec exec;
	int i;

	exec->cmd_count = find_size_cmd(exec->cmd_list);
	if (exec->cmd_count < 1)
		return (usage());
	exec = parsing_exec(exec, envp);
	if (exec == NULL)
		free_exec();
	exec->pids = malloc(sizeof(pid_t) * exec->cmd_count);
	if (!exec->pids)
		free_pipex(exec, -1, "pipex: malloc: %s\n", strerror(errno));
	i = -1;
	if (exec->cmd_count > 1)
		while (++i < exec->cmd_count)
			child_process(exec, i, envp);
	else
			exec_one(exec, envp);
	i = -1;
	while (++i < exec->cmd_count)
		waitpid(exec->pids[i], &exec->exit_status, 0);
	free_pipex_core(exec);
	if (WIFEXITED(exec->exit_status))
		return (WEXITSTATUS(exec->exit_status));
	return (exec->exit_status);
}
