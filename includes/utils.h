/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:46:54 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/15 20:29:10 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	ft_message(char *str, char *str2);
int		usage(void);
void	free_split(char **arr);
void	free_triple(char ***triple);
void	free_token(t_token *token, int status, char *str, char *str2);
void	free_pipex(t_exec *exec, int status, char *str, char *str2);
void	free_pipex_core(t_exec *exec);
void	ft_close(t_exec *exec, t_type type);
void	free_exec(t_exec *exec, int status, char *str, char *str2);
t_exec	*free_exec_list(t_exec *exec, char *str, char *str2);
t_cmd	*find_last_cmd(t_cmd *lst);
t_args	*find_last_args(t_args *lst);
t_files	*find_last_files(t_files *lst);
t_cmd	*find_first_cmd(t_cmd *lst);
t_args	*find_first_args(t_args *lst);
t_files	*find_first_files(t_files *lst);
int		find_size(t_token *lst);
int		find_size_cmd(t_cmd *lst);
int		find_size_args(t_args *lst);
char	*ft_strjoin_space(char const *s1, char const *s2);
#endif