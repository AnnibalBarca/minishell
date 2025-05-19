/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:40:14 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/19 18:07:49 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_value(char **envp, const char *key)
{
	int	i;
	int	key_len;

	if (!envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (ft_strdup(envp[i] + key_len + 1));
		i++;
	}
	return (NULL);
}

static int	update_env_variable(char ***env_ptr, const char *name,
		const char *value)
{
	char	*env_entry;
	int		i;
	int		name_len;
	char	**env;

	env = *env_ptr;
	if (!name || !value)
		return (0);
	env_entry = ft_strjoin3(name, "=", value);
	if (!env_entry)
		return (0);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			free(env[i]);
			env[i] = env_entry;
			return (1);
		}
		i++;
	}
	free(env_entry);
	return (0);
}

static int	change_directory(const char *path, char ***env_ptr)
{
	char	current_dir[PATH_MAX];
	char	new_dir[PATH_MAX];

	if (!getcwd(current_dir, PATH_MAX))
	{
		perror("minishell: cd");
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		return (1);
	}
	if (!getcwd(new_dir, PATH_MAX))
	{
		perror("minishell: cd");
		return (1);
	}
	update_env_variable(env_ptr, "OLDPWD", current_dir);
	update_env_variable(env_ptr, "PWD", new_dir);
	return (0);
}

int	builtin_cd(char **args, char ***env_ptr)
{
	char *home_dir;
	char *old_pwd;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		home_dir = get_env_value(*env_ptr, "HOME");
		if (!home_dir)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (1);
		}
		change_directory(home_dir, env_ptr);
		free(home_dir);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		old_pwd = get_env_value(*env_ptr, "OLDPWD");
		if (!old_pwd)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
			return (1);
		}
		ft_putendl_fd(old_pwd, STDOUT_FILENO);
		change_directory(old_pwd, env_ptr);
		free(old_pwd);
	}
	else
		return (change_directory(args[1], env_ptr));
	return (0);
}