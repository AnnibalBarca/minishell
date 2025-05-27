/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:53 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/27 16:13:07 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	ft_message(char *str, char *str2);
int		usage(void);
void	free_split(char **arr);
void	free_triple(char ***triple);

// structs
char	**safe_realloc_string_array(char **old_array, size_t new_size);

// t_exec management 1!!!
t_exec	*find_last(t_exec *lst);
t_exec	*find_first(t_exec *lst);
void	open_infile(t_exec *exec, char *infile);
void	open_outfile(t_exec *exec, char *outfile, int mode);
void	free_token(t_token *token, int status, char *str, char *str2);
void	free_pipex(t_exec *exec, int status, char *str, char *str2);
void	free_pipex_core(t_exec *exec);
void	ft_close(t_exec *exec, t_type type);
void	free_exec(t_exec *exec, int status, char *str, char *str2);
void	open_infile(t_exec *exec, char *infile);
int		open_infile_exec(t_exec *exec, char *infile);
void	open_outfile(t_exec *exec, char *outfile, int mode);
int		open_outfile_exec(t_exec *exec, char *outfile, int mode);

// t_token + t_syntax
t_token	*safe_create_token(char *value, t_token_type type, t_quote quote);
int		find_size(t_token *lst);
char	*safe_strdup_or_cleanup(const char *src, char **line, t_token **tokens);
int		safe_cleanup_and_return_null(char **line, t_token **tokens,
			t_syntax_result *result, char ***accumulated_input);
void	cleanup_syntax_result(t_syntax_result *result);

// t_context

#endif