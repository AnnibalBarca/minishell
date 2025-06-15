/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:43:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/14 20:45:07 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*random_filename(t_exec *exec)
{
	char			*filename;
	int				urandom_fd;
	unsigned char	random;
	int				i;

	i = -1;
	filename = malloc(sizeof(char) * 9);
	if (!filename)
		free_pipex(exec, 1, "malloc", strerror(errno));
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		free_pipex(exec, 1, "open", strerror(errno));
	while (++i < 8)
	{
		if (read(urandom_fd, &random, 1) < 0)
		{
			close(urandom_fd);
			free_pipex(exec, 1, "read", strerror(errno));
		}
		filename[i] = CHARSET[random % (sizeof(CHARSET) - 1)];
	}
	filename[8] = '\0';
	close(urandom_fd);
	return (filename);
}

void	here_doc(t_exec *exec, char *limiter)
{
	char	*temp;
	int		infile;

	free(exec->cmd_list->args->cmd_args);
	exec->cmd_list->args->cmd_args = random_filename(exec);
	infile = open(exec->cmd_list->args->cmd_args,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	temp = readline("> ");
	if (!temp)
		free_pipex(exec, 1, "malloc", strerror(errno));
	while (temp != NULL)
	{
		if (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(temp) == ft_strlen(limiter))
		{
			free(temp);
			break ;
		}
		write(infile, temp, ft_strlen(temp));
		write(infile, "\n", 1);
		free(temp);
		temp = readline("> ");
		if (!temp)
			free_pipex(exec, 1, "malloc:", strerror(errno));
	}
	close(infile);
	infile = open(exec->cmd_list->args->cmd_args, O_RDONLY);
}
