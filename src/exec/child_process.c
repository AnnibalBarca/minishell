/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/29 15:48:18 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	child_process(t_exec *exec, int cmd_index, char **envp)
{
	exec->pids[cmd_index] = fork();
	if (exec->pids[cmd_index] == -1)
		free_child(exec, 1, "fork", strerror(errno));
	if (exec->pids[cmd_index] == 0)
	{
		setup_child_signals();
		execute_child(exec, cmd_index, envp);
	}
}

int	is_infile(t_exec *exec, t_files *current)
{
	int	previous_input_fd;

	previous_input_fd = -1;
	exec->cmd_list->fd_input = -1;
	if (previous_input_fd != -1)
		safe_close(&previous_input_fd);
	if (access(current->infile_name, F_OK) == -1)
	{
		free_child(exec, 1, current->infile_name, "No such file or directory");
		return (1);
	}
	exec->cmd_list->fd_input = open(current->infile_name, O_RDONLY);
	if (exec->cmd_list->fd_input == -1)
	{
		free_child(exec, 1, current->infile_name, strerror(errno));
		return (1);
	}
	previous_input_fd = exec->cmd_list->fd_input;
	return (0);
}

int	is_outfile(t_exec *exec, t_files *current, int *previous_output_fd)
{
	int	flags;

	if (*previous_output_fd != -1)
		safe_close(previous_output_fd);
	if (access(current->outfile_name, F_OK) == 0
		&& access(current->outfile_name, W_OK) == -1)
	{
		free_child(exec, 1, current->outfile_name, "Permission denied");
	}
	flags = O_WRONLY | O_CREAT;
	if (current->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	exec->cmd_list->fd_output = open(current->outfile_name, flags, 0644);
	if (exec->cmd_list->fd_output == -1)
	{
		free_child(exec, 1, current->outfile_name, strerror(errno));
	}
	*previous_output_fd = exec->cmd_list->fd_output;
	return (0);
}

void	process_redirections(t_exec *exec)
{
	t_files	*current;
	int		previous_output_fd;

	previous_output_fd = -1;
	exec->cmd_list->fd_output = -1;
	if (!exec->cmd_list->files)
		return ;
	current = exec->cmd_list->files;
	while (current)
	{
		if (current->infile_name)
		{
			if (is_infile(exec, current))
				return ;
		}
		if (current->outfile_name)
		{
			if (is_outfile(exec, current, &previous_output_fd))
				return ;
		}
		current = current->next;
	}
}

void	execute_child(t_exec *exec, int cmd_index, char **envp)
{
	process_redirections(exec);
	if (exec->cmd_list->fd_input == -2 || exec->cmd_list->fd_output == -2)
		exit(1);
	setup_pipe_redirections(exec, cmd_index);
	close_all_pipes(exec);
	close_child_fds(exec);
	exec->cmd_list->args = find_first_args(exec->cmd_list->args);
	if (!exec->cmd_list->args || !exec->cmd_list->args->cmd_args
		|| !*exec->cmd_list->args->cmd_args)
		free_child(exec, 127, "", "command not found");
	ft_execute(exec, envp);
}
