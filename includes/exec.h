/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:46:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/15 20:40:24 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"

void	free_pipex(t_exec *exec, int status, char *str, char *str2);
void	free_exec(t_exec *exec, int status, char *str, char *str2);
void	ft_message(char *str, char *str2);
void	free_triple(char ***triple);
t_exec	*split_pipeline_groups(t_token *tokens);
void	child_process(t_exec *exec, char *argv, char **envp);
void		here_doc(t_exec *exec, char *limiter);
void	pipex_init(t_exec *exec, char **envp);
void	find_path(t_exec *exec, char *cmd);
void	execute_bonus(t_exec *exec, char *argv, char **envp);
int		pipex(t_exec *exec, int ac, char **av, char **envp);
void	exec_one(t_exec *exec, char *argv, char **envp);
int	open_infile(t_exec *exec, int previous_fd);
int	open_outfile(t_exec *exec, int previous_fd);

void	random_filename(t_exec *exec);
t_cmd	*parsing_cmd(t_token *tokens);
t_exec	*parsing_exec(t_token *tokens, char **envp);

#endif