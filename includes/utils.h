/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:53 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/09 16:41:48 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	open_infile(t_exec *exec, char *infile);
void	open_outfile(t_exec *exec, char *outfile, int mode);
int		usage(void);
void	free_split(char **arr);
void	free_triple(char ***triple);
void	free_token(t_token *token, int status, char *str, char *str2);
void	free_pipex(t_exec *exec, int status, char *str, char *str2);
void	ft_close(t_exec *exec, t_type type);
void	free_exec(t_exec *exec, int status, char *str, char *str2);
void	open_infile(t_exec *exec, char *infile);
void	open_infile_exec(t_exec *exec, char *infile);
void	open_outfile(t_exec *exec, char *outfile, int mode);
void	open_outfile_exec(t_exec *exec, char *outfile, int mode);

#endif