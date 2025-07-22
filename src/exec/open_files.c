/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:23:18 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/21 15:40:33 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_here_doc(t_files *files)
{
	int	fd;

	fd = open(files->infile_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_message("<open_infile>", strerror(errno), NULL);
		return (-1);
	}
	if (access(files->infile_name, F_OK) == -1)
	{
		ft_message("No such file or directory", files->infile_name, NULL);
		return (-1);
	}
	return (fd);
}

int	check_infile(t_exec *exec, t_files **current)
{
	if (access((*current)->infile_name, F_OK) == -1)
	{
		ft_message(NULL, (*current)->infile_name, "No such file or directory");
		exec->cmd_list->fd_input = -2;
		exec->has_input_error = 1;
		return (1);
	}
	if (access((*current)->infile_name, R_OK) == -1)
	{
		ft_message(NULL, (*current)->infile_name, "Permission denied");
		exec->cmd_list->fd_input = -2;
		exec->has_input_error = 1;
		return (1);
	}
	return (0);
}

int	check_input(t_exec *exec, t_files **current)
{
	if (exec->cmd_list->fd_input == -1)
	{
		ft_message((*current)->infile_name, strerror(errno), NULL);
		exec->cmd_list->fd_input = -2;
		exec->has_input_error = 1;
		return (1);
	}
	return (0);
}

void	struct_open_infile(t_exec *exec)
{
	t_files	*current;
	int		previous_fd;

	exec->cmd_list->fd_input = -1;
	previous_fd = -1;
	if (!exec->cmd_list->files)
		return ;
	current = exec->cmd_list->files;
	while (current)
	{
		if (current->infile_name)
		{
			if (previous_fd != -1)
				safe_close(&previous_fd);
			if (check_infile(exec, &current))
				return ;
			exec->cmd_list->fd_input = open(current->infile_name, O_RDONLY);
			if (check_input(exec, &current))
				return ;
			previous_fd = exec->cmd_list->fd_input;
		}
		current = current->next;
	}
}

int	check_outfile(t_exec *exec, t_files **current, int *flags)
{
	if (access((*current)->outfile_name, F_OK) == 0
		&& access((*current)->outfile_name, W_OK) == -1)
	{
		ft_message(NULL, (*current)->outfile_name, "Permission denied");
		exec->cmd_list->fd_output = -2;
		return (1);
	}
	*flags = O_WRONLY | O_CREAT;
	if ((*current)->append)
		*flags |= O_APPEND;
	else
		*flags |= O_TRUNC;
	exec->cmd_list->fd_output = open((*current)->outfile_name, *flags, 0644);
	return (0);
}

int	check_output(t_exec *exec, t_files **current)
{
	if (exec->cmd_list->fd_output == -1)
	{
		ft_message(NULL, (*current)->outfile_name, strerror(errno));
		exec->cmd_list->fd_output = -2;
		return (1);
	}
	return (0);
}

void	struct_open_outfile(t_exec *exec)
{
	t_files	*current;
	int		previous_fd;
	int		flags;

	if (exec->has_input_error)
		return ;
	exec->cmd_list->fd_output = -1;
	previous_fd = -1;
	if (!exec->cmd_list->files)
		return ;
	current = exec->cmd_list->files;
	while (current)
	{
		if (current->outfile_name)
		{
			if (previous_fd != -1)
				safe_close(&previous_fd);
			if (check_outfile(exec, &current, &flags))
				return ;
			if (check_output(exec, &current))
				return ;
			previous_fd = exec->cmd_list->fd_output;
		}
		current = current->next;
	}
}
