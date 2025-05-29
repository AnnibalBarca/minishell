/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:55:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/29 16:02:55 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "utils.h"



t_token *expand_tokens_and_update_env(t_token *tokens, char **envp, int exit_status, char ***updated_envp);
char			**export_variable(char **envp, const char *name,
					const char *value);
int				is_export_assignment(const char *str);
char			**process_export_token(t_token *token, char **envp);

int builtin_echo(char **args, char ***env_ptr);
int builtin_cd(char **args, char ***env_ptr);
int builtin_pwd(char **args, char ***env_ptr);
int builtin_export(char **args, char ***env_ptr);
int builtin_unset(char **args, char ***env_ptr);
int builtin_env(char **args, char ***env_ptr);
int builtin_exit(char **args);

int is_builtin(char *cmd);
int execute_builtin(char **args, char ***env_ptr);


#endif