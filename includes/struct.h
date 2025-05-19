/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:36:22 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/19 20:15:25 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/all.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define CHARSET "abcdefghijklmnopqrstuvwxyz"

typedef struct s_str_builder
{
	char			*str;
	size_t			len;
	size_t			capacity;
}					t_str_builder;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}					t_token_type;

typedef enum e_type
{
	CMD,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	FD0,
	FD1
}					t_type;

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}					t_quote;

typedef struct s_word_segment
{
	char					*value;
	t_quote					quote_type;
	struct s_word_segment	*next;
}							t_word_segment;


typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote			quote;
	t_word_segment	*segments;
	struct s_token	*next;
}					t_token;

typedef enum e_env
{
	NO_ENV,
	ENV
}					t_env;

typedef struct s_pipex
{
	pid_t			*pids;
	char			*cmd;
	char			**cmd_args;
	char			**paths;
	char			*path;
	int				infile;
	int				outfile;
	char			*infile_name;
	char			*outfile_name;
	int				fd[2];
	int				status;
	int				here_doc;
	int				append;
	int				cmd_nbr;
	int				i_wait;
	int				i;
	int				envp;
}					t_pipex;

typedef struct s_exec
{
	int				count;
	char			***groups;
	char			**cmds;
	int				i;
	int				ncmd;
	int				ng;
	char			**infile_name;
	char			**outfile_name;
	int				*append;
	int				infile;
	int				outfile;
	char			**group;
	int				total;
	int				idx;
	int				j;
	int				redir;
	int				redir_in;
	int				redir_out;
	t_pipex			pipex;
}					t_exec;

extern int g_exit_status; // For the shell's exit status
extern volatile sig_atomic_t g_signal_received; // To flag if a signal was caught

#endif