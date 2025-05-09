/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:44:43 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 19:28:44 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* ---------- pretty‑print helpers --------------------------------------- */

static void  print_str_array(char **a)
{
	int i = 0;

	if (!a)
	{
		printf("NULL");
		return ;
	}
	while (a[i])
	{
		printf("\"%s\"", a[i]);
		if (a[i + 1])
			printf(", ");
		i++;
	}
}

static void  dump_cmd_list(t_cmd *c)
{
	int idx = 0;

	while (c)
	{
		printf("┌─ command %d ────────────────────────────────────────────\n", idx++);
		printf("│  cmd         : %s\n", c->cmd ? c->cmd : "NULL");
		printf("│  cmd_args    : ");
		print_str_array(c->cmd_args);
		printf("\n│  infile_name : %s\n", c->infile_name ? c->infile_name : "NULL");
		printf("│  outfile_name: %s\n", c->outfile_name ? c->outfile_name : "NULL");
		printf("│  here_doc    : %s\n", (c->here_doc == HEREDOC) ? "HEREDOC" : "NO");
		printf("│  pipe fds    : [%d, %d]\n", c->fd[0], c->fd[1]);
		printf("└────────────────────────────────────────────────────────\n\n");
		c = c->next;
	}
}

/* ---------- small wrapper around your ft_parsing ----------------------- */

static void  one_test(const char *input, char **envp, int last_exit)
{
	printf("\n================  \"%s\"  ================\n", input);
	t_cmd *tree = ft_parsing((char *)input, envp, last_exit);
	if (!tree)
	{
		printf(" => parsing returned NULL (syntax error?)\n");
		return ;
	}
	dump_cmd_list(tree);
	free_cmd_list(tree);  /* your silent list destructor */
}

/* ---------- main ------------------------------------------------------- */

int	main(int ac, char **av, char **envp)
{
	(void)ac; (void)av;

	const char *tests[] = {
		/* ───── SIMPLE WORDS / ARGS ───────────────────────────────────────────── */
			"grep pattern << LIMIT | wc -l",
		
		/* ───── QUOTING ───────────────────────────────────────────────────────── */
			"echo '$USER literal' \"and $USER expanded\"",
			"echo \"double \\\" inner\" 'single \" inside'",
		
		/* ───── ENV‑EXPANSION ─────────────────────────────────────────────────── */
			"echo $HOME",
			"echo $UNDEFINED_VAR end",
			"echo first=$FIRST second=$SECOND",   /* set in your shell before run */
		
		/* ───── REDIRECTIONS ──────────────────────────────────────────────────── */
			"cat < infile.txt",
			"grep foo < in1.txt > out1.txt",
			"echo hi >> append.log",
			"sort < unsorted.txt | uniq | wc -l > count.txt",
		
		/* ───── PIPES (with and without spaces) ───────────────────────────────── */
			"ls -1 | wc -l",
			"ps ax|grep mysql|awk '{print $1}'",
		
		/* ───── HEREDOCS ──────────────────────────────────────────────────────── */
			
		/*  for those two you’ll be prompted; type a few lines then the delimiter  */
		
		/* ───── MIXED QUOTES + EXPANSION IN PIPES ─────────────────────────────── */
			"echo \"User is $USER\" | cat -n",
		
		/* ───── SYNTAX‑ERROR CASES (should return NULL) ───────────────────────── */
			"< infile ls",          /* redirection before command              */
			"echo unmatched \"",    /* unclosed quote                          */
			"ls | | wc",            /* double pipe                             */
			"cat > ",               /* redirect without file                   */
		
		/* ───── START / END MARKERS ───────────────────────────────────────────── */
			NULL
		};		
	for (int i = 0; tests[i]; i++)
		one_test(tests[i], envp, 42);   /* use 42 as previous exit status */

	return (0);
}
