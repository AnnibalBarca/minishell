/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:43:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/18 11:40:19 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int free_infile_name(t_files *files)
{
	free(files->infile_name);
	files->infile_name = NULL;
	return (1);
}

int	random_filename(t_files *files)
{
	int				urandom_fd;
	unsigned char	random;
	int				i;

	if (!files || !(files->infile_name = malloc(sizeof(char) * 22)))
		return (1);
	ft_strcpy(files->infile_name, "/tmp/.heredoc_");
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		return (free_infile_name(files));
	i = 14;
	while (i < 21)
	{
		if (read(urandom_fd, &random, 1) < 0)
		{
			safe_close(&urandom_fd);
			free(files->infile_name);
			files->infile_name = NULL;
			return (1);
		}
		files->infile_name[i++] = CHARSET[random % (sizeof(CHARSET) - 1)];
	}
	files->infile_name[21] = '\0';
	safe_close(&urandom_fd);
	return (0);
}

char	*here_doc(t_files *files, char *limiter)
{
	char	*temp;
	int		fd;

	setup_heredoc_signals();
	if (random_filename(files) == 1)
		return (NULL);
	fd = open_here_doc(files);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		temp = readline("> ");
		if (!temp)
		{
			safe_close(&fd);
			if (g_signal_test == 130)
			{
				unlink(files->infile_name);
				return (NULL);
			}
			break ;
		}
		if (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(temp) == ft_strlen(limiter))
		{
			free(temp);
			break ;
		}
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		free(temp);
	}
	safe_close(&fd);
	reset_signals();
	return (files->infile_name);
}
