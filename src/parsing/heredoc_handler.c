/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:20:16 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/26 14:29:18 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/syntax.h"

static char	*generate_temp_heredoc_filename(void)
{
	static int	heredoc_id = 0;
	char		*id_str;
	char		*filename_part;
	char		*full_filename;

	id_str = ft_itoa(heredoc_id++);
	if (!id_str)
		return (NULL);
	filename_part = ft_strjoin("minishell_heredoc_", id_str);
	free(id_str);
	if (!filename_part)
		return (NULL);
	full_filename = ft_strjoin("/tmp/", filename_part);
	free(filename_part);
	return (full_filename);
}

bool	was_delimiter_quoted(t_token *delimiter_token)
{
	t_word_segment	*seg;

	if (!delimiter_token || delimiter_token->type != T_WORD)
		return (false);
	if (delimiter_token->quote == Q_SINGLE
		|| delimiter_token->quote == Q_DOUBLE)
		return (true);
	seg = delimiter_token->segments;
	while (seg)
	{
		if (seg->quote_type == Q_SINGLE || seg->quote_type == Q_DOUBLE)
			return (true);
		seg = seg->next;
	}
	return (false);
}

static int	initialize_heredoc_read(t_token *del_token, char **filename_ptr,
		bool *expand_ptr)
{
	int	fd;

	if (!del_token || !del_token->value)
		return (-1);
	*expand_ptr = !was_delimiter_quoted(del_token);
	*filename_ptr = generate_temp_heredoc_filename();
	if (!*filename_ptr)
		return (-1);
	fd = open(*filename_ptr, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(*filename_ptr);
		*filename_ptr = NULL;
		report_syntax_error_detail("failed to create heredoc temp file", NULL);
		return (-1);
	}
	return (fd);
}

static void	write_processed_heredoc_line(int fd, char *line_content,
		bool expand, char **envp, int exit_s)
{
	char	*processed_line;

	if (expand)
	{
		processed_line = expand_variables_in_str(line_content, Q_DOUBLE, envp,
				exit_s);
		if (processed_line)
		{
			ft_putendl_fd(processed_line, fd);
			free(processed_line);
		}
		else
			ft_putendl_fd(line_content, fd);
	}
	else
		ft_putendl_fd(line_content, fd);
}

static void	heredoc_read_loop(int fd, t_token *del_token, bool expand,
		char **envp, int exit_s)
{
	char	*current_line;

	while (1)
	{
		current_line = secure_readline("heredoc> ");
		if (!current_line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by "
							"end-of-file (wanted `",
							STDERR_FILENO);
			ft_putstr_fd((char *)del_token->value, STDERR_FILENO);
			ft_putstr_fd("')\n", STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(current_line, del_token->value) == 0)
		{
			free(current_line);
			break ;
		}
		write_processed_heredoc_line(fd, current_line, expand, envp, exit_s);
		free(current_line);
	}
}

char	*read_heredoc_content(t_token *delimiter_token, char **envp,
		int last_exit_status, t_main_loop_state *loop_state)
{
	char *temp_filename;
	int fd;
	bool expand_content_vars;

	(void)loop_state;
	temp_filename = NULL;
	fd = initialize_heredoc_read(delimiter_token, &temp_filename,
			&expand_content_vars);
	if (fd == -1)
		return (NULL);
	heredoc_read_loop(fd, delimiter_token, expand_content_vars, envp,
		last_exit_status);
	// if (close(fd) == -1)
	// {
	// }
	return (temp_filename);
}
