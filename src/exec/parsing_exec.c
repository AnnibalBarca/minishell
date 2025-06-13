/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:39:17 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/13 19:50:34 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_init(t_exec *exec, char **envp)
{
	size_t	i;

	ft_memset(exec, 0, sizeof(t_exec));
	exec->envp = envp;
	exec->envp_exists = 1;
	exec->stdin_backup = dup(STDIN_FILENO);
	exec->stdout_backup = dup(STDOUT_FILENO);
	i = 0;
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp || !envp[i])
	{
		exec->envp_exists = 0;
		return ;
	}
	exec->paths = ft_split(envp[i] + 5, ':');
	// if (!exec->paths)
	// 	exec_error(exec, 1, "minishell: malloc: %s\n", strerror(errno));
}

t_exec *parsing_exec(t_token *tokens, char **envp)
{
	t_cmd *cmd;
	t_exec *exec;
	if (!tokens)
		return (NULL);
	cmd = parsing_cmd(tokens);
	if (!cmd)
		return (NULL);
	exec = malloc(sizeof(t_exec));
	if (!exec)
	{
		//free_cmd()
		return (NULL);
	}
	exec_init(exec, envp);
	exec->cmd_list = cmd;
	return (exec);
}
