/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:47:43 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/14 21:26:04 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	**struct_to_array(t_args *args)
{
	char	**array;
	t_args	*current;
	int		size;
	int		i;

	if (!args)
		return (NULL);
	size = find_size_args(args);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	current = args;
	i = 0;
	while (current && i < size)
	{
		array[i] = current->cmd_args;
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	is_directory(t_exec *exec)
{
	if (ft_strchr(exec->cmd_list->args->cmd_args, '/'))
	{
		ft_message(exec->cmd_list->args->cmd_args, "Is a directory");
		if (access(exec->cmd_list->args->cmd_args, F_OK) == -1)
			exec_error(exec, 127, "minishell: %s: No such file or directory\n",
				exec->cmd_list->args->cmd_args);
		if (access(exec->cmd_list->args->cmd_args, X_OK) == -1)
			exec_error(exec, 126, "minishell: %s: Permission denied\n",
				exec->cmd_list->args->cmd_args);
		return (1);
	}
	return (0);
}

void	check_exec_file(t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_pipex(exec, 127, cmd, "No such file or directory");
	if (access(cmd, X_OK) == -1)
		free_pipex(exec, 126, cmd, "Permission denied");
	exec->cmd_list->cmd_path = cmd;
}

void	check_exec(t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_pipex(exec, 127, cmd, "command not found");
	if (access(cmd, X_OK) == -1)
		free_pipex(exec, 126, cmd, "Permission denied");
}

void	find_path(t_exec *exec, char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (access(cmd, F_OK) == 0)
	{
		check_exec_file(exec, cmd);
		return ;
	}
	while (exec->paths && exec->envp && exec->paths[++i])
	{
		tmp = ft_strjoin(exec->paths[i], "/");
		if (!tmp)
			free_pipex(exec, 1, "malloc", strerror(errno));
		exec->cmd_list->cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!exec->cmd_list->cmd_path)
			free_pipex(exec, 1, "malloc", strerror(errno));
		if (access(exec->cmd_list->cmd_path, F_OK) == 0)
			break ;
		free(exec->cmd_list->cmd_path);
		exec->cmd_list->cmd_path = NULL;
	}
	if (exec->cmd_list->cmd_path)
		check_exec(exec, exec->cmd_list->cmd_path);
}

void	execute_bonus(t_exec *exec, char *argv, char **envp)
{
	exec->cmd_list->args = find_first_args(exec->cmd_list->args);
	if (exec->cmd_list->args->cmd_args == NULL)
		free_pipex(exec, 127, argv, "Command not found");
	if (is_directory(exec) == 1)
		return ;
	find_path(exec, exec->cmd_list->args->cmd_args);
	if (!exec->cmd_list->cmd_path)
		free_pipex(exec, 127, exec->cmd_list->args, "Command not found");
	if (execve(exec->cmd_list->cmd_path, struct_to_array(exec->cmd_list->args),
			envp) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
			free_pipex(exec, 126, "pipex: execve", strerror(errno));
		if (errno == ENOENT || errno == EPERM)
			free_pipex(exec, 127, "pipex: execve", strerror(errno));
		if (errno == ENOTDIR)
			free_pipex(exec, 127, "pipex: execve", strerror(errno));
		free_pipex(exec, 1, "execve", strerror(errno));
	}
}
