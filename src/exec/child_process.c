/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/21 15:18:19 by nagaudey         ###   ########.fr       */
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
		ft_message(NULL, current->infile_name, "No such file or directory");
		exec->cmd_list->fd_input = -2;
		return (1);
	}
	exec->cmd_list->fd_input = open(current->infile_name, O_RDONLY);
	if (exec->cmd_list->fd_input == -1)
	{
		ft_message(NULL, current->infile_name, strerror(errno));
		exec->cmd_list->fd_input = -2;
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
		ft_message(NULL, current->outfile_name, "Permission denied");
		exec->cmd_list->fd_output = -2;
		return (1);
	}
	flags = O_WRONLY | O_CREAT;
	if (current->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	exec->cmd_list->fd_output = open(current->outfile_name, flags, 0644);
	if (exec->cmd_list->fd_output == -1)
	{
		ft_message(NULL, current->outfile_name, strerror(errno));
		exec->cmd_list->fd_output = -2;
		return (1);
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
	execute_bonus(exec, envp);
}

void	secure_dup(int old_fd, int new_fd, t_exec *exec)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		free_child(exec, 1, "dup2", strerror(errno));
	}
}

void	setup_pipe_redirections(t_exec *exec, int cmd_index)
{
	if (cmd_index == 0)
	{
		if (exec->cmd_list->fd_input != -1)
			secure_dup(exec->cmd_list->fd_input, STDIN_FILENO, exec);
		if (exec->cmd_list->fd_output != -1)
			secure_dup(exec->cmd_list->fd_output, STDOUT_FILENO, exec);
		else if (exec->cmd_count > 1)
			secure_dup(exec->pipes[0][1], STDOUT_FILENO, exec);
	}
	else if (cmd_index == exec->cmd_count - 1)
	{
		if (exec->cmd_list->fd_input != -1)
			secure_dup(exec->cmd_list->fd_input, STDIN_FILENO, exec);
		else
			secure_dup(exec->pipes[cmd_index - 1][0], STDIN_FILENO, exec);
		if (exec->cmd_list->fd_output != -1)
			secure_dup(exec->cmd_list->fd_output, STDOUT_FILENO, exec);
	}
	else
	{
		secure_dup(exec->pipes[cmd_index - 1][0], STDIN_FILENO, exec);
		secure_dup(exec->pipes[cmd_index][1], STDOUT_FILENO, exec);
	}
}
