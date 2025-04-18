/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/09 21:24:53 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1>"
		"<...> <file>\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_parse(t_pipex *pipex, char **av, int ac)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && av[1][8] == '\n')
	{
		if (ac < 6)
		{
			pipex->here_doc = 0;
			free_parent(pipex, -1, NULL, NULL);
			usage();
		}
		random_filename(pipex);
		here_doc(pipex, av[2]);
		open_outfile(pipex, av[ac - 1], 0);
	}
	else
	{
		pipex->here_doc = 0;
		open_outfile(pipex, av[ac - 1], 1);
		open_infile(pipex, av[1]);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
		usage();
	pipex_init(&pipex, envp);
	ft_parse(&pipex, av, ac);
	pipex.cmd_nbr = ac - 3 - pipex.here_doc;
	pipex.pids = malloc(sizeof(pid_t) * (pipex.cmd_nbr));
	if (!pipex.pids)
		ft_printf_error(-1, "pipex: malloc: %s\n", strerror(errno));
	while (++pipex.i < pipex.cmd_nbr)
		child_process(&pipex, av[pipex.i + 2 + pipex.here_doc], envp);
	while (++pipex.i_wait < pipex.cmd_nbr)
		waitpid(pipex.pids[pipex.i_wait], &pipex.status, 0);
	free_parent(&pipex, -1, NULL, NULL);
	if (WIFEXITED(pipex.status))
		return (WEXITSTATUS(pipex.status));
	return (pipex.status);
}

