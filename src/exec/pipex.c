/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/20 17:36:36 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	free_pipes(t_exec *exec, int failed_index)
{
	int	j;

	j = 0;
	while (j < failed_index)
	{
		if (exec->pipes[j])
		{
			if (exec->pipes[j][0] != -1)
				safe_close(&exec->pipes[j][0]);
			if (exec->pipes[j][1] != -1)
				safe_close(&exec->pipes[j][1]);
			free(exec->pipes[j]);
		}
		j++;
	}
	free(exec->pipes);
	exec->pipes = NULL;
}

void	create_pipes(t_exec *exec)
{
	int	i;

	if (!exec || exec->cmd_count <= 1)
		return ;
	exec->pipes = ft_calloc(exec->cmd_count - 1, sizeof(int *));
	if (!exec->pipes)
		free_parent(exec, 1, "Error create_pipes", NULL);
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		exec->pipes[i] = ft_calloc(2, sizeof(int));
		if (!exec->pipes[i])
		{
			free_pipes(exec, i);
			free_parent(exec, 1, "Error create_pipes", NULL);
		}
		if (pipe(exec->pipes[i]) == -1)
		{
			free(exec->pipes[i]);
			free_pipes(exec, i);
			free_parent(exec, 1, "Error create_pipes", NULL);
		}
		i++;
	}
}

int	pipex(t_token *tokens, char ***envp_ptr)
{
	t_exec	exec;
	int		i;
	t_cmd	*head;
	int		status;

	exec_init(&exec, *envp_ptr);
	parsing_exec(tokens, &exec);
	if (!exec.cmd_list)
		return (1);
	exec.cmd_count = find_size_cmd(exec.cmd_list);
	head = exec.cmd_list;
	if (exec.cmd_count == 1 && exec.cmd_list->is_builtin)
	{
		exec.exit_status = execute_single_builtin_in_parent(&exec, envp_ptr);
		return (exec.exit_status);
	}
	setup_parent_signals();
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		return (1);
	create_pipes(&exec);
	i = -1;
	while (++i < exec.cmd_count)
	{
		child_process(&exec, i, *envp_ptr);
		exec.cmd_list = exec.cmd_list->next;
	}
	i = -1;
	close_all_pipes(&exec);
	while (++i < exec.cmd_count)
	{
		waitpid(exec.pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			ft_putchar_fd('\n', 2);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		if (i == exec.cmd_count - 1)
		{
			if (WIFEXITED(status))
				exec.exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				exec.exit_status = 128 + WTERMSIG(status);
		}
	}
	exec.cmd_list = head;
	free_parent(&exec, -1, NULL, NULL);
	setup_interactive_signals();
	return (exec.exit_status);
}
