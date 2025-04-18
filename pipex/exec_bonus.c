/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 02:36:30 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/09 20:48:07 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_exec_file(t_pipex *pipex, char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd, 2);
		free_parent(pipex, 127, ": no such file or directory\n", NULL);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd, 2);
		free_parent(pipex, 126, ": Permission denied\n", NULL);
	}
	pipex->cmd = cmd;
}

void	check_exec(t_pipex *pipex, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_parent(pipex, 127, "pipex: %s: Command not found\n", cmd);
	if (access(cmd, X_OK) == -1)
		free_parent(pipex, 126, "pipex: %s: Permission denied\n", cmd);
}

void	find_path(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (access(cmd, F_OK) == 0)
	{
		check_exec_file(pipex, cmd);
		return ;
	}
	while (pipex->envp && pipex->paths[++i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		if (!tmp)
			free_parent(pipex, 1, "pipex: malloc: %s\n", strerror(errno));
		pipex->cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!pipex->cmd)
			free_parent(pipex, 1, "pipex: malloc: %s\n", strerror(errno));
		if (access(pipex->cmd, F_OK) == 0)
			break ;
		free(pipex->cmd);
		pipex->cmd = NULL;
	}
	if (pipex->cmd)
		check_exec(pipex, pipex->cmd);
}

void	execute_bonus(t_pipex *pipex, char *argv, char **envp)
{
	pipex->cmd_args = ft_split(argv, ' ');
	if (pipex->cmd_args[0] == NULL)
		free_parent(pipex, 127, "pipex: %s: Command not found\n", argv);
	find_path(pipex, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(pipex->cmd_args[0], 2);
		free_parent(pipex, 127, "pipex %s: Command not found\n", argv);
	}
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
			free_parent(pipex, 126, "pipex: execve: %s\n", strerror(errno));
		if (errno == ENOENT || errno == EPERM)
			free_parent(pipex, 127, "pipex: execve: %s\n", strerror(errno));
		if (errno == ENOTDIR)
			free_parent(pipex, 127, "pipex: execve: %s\n", strerror(errno));
		free_parent(pipex, 1, "pipex: execve: %s\n", strerror(errno));
	}
}

