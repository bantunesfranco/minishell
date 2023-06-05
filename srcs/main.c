/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:01:01 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/05 18:00:58 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

void	minishell_loop(t_gen *gen)
{
	char		*line;
	char		*line2;
	t_pipeline	*input;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			line = readline("minishell$ ");
			if (line == NULL && errno == ENOMEM)
				err_msg(NULL, "line");
			else if (line == NULL)
			{
				if (write(STDOUT_FILENO, "exit\n", 5) == -1)
					err_msg(NULL, "write");
				exit(0);
			}
			if (ft_strlen(line))
				add_history(line);
		}
		else
		{
			line2 = get_next_line(STDIN_FILENO);
			if (line2 == NULL)
				err_msg(NULL, "line");
			else if (line == NULL)
			{
				if (write(STDOUT_FILENO, "exit\n", 5) == -1)
					err_msg(NULL, "write");
				exit(0);
			}
			line = ft_strtrim(line2, "\n");
			free(line2);
		}
		input = parse_line(line);
		free(line);
		if (input != NULL)
			executor(gen, input);
		free_parsed_structs(input);
	}
}

void	leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_gen	gen;
	char	**start_env;

	// atexit(leaks);
	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("minishell: too many args", 2);
		return (1);
	}
	start_env = ft_arrdup(envp);
	if (!start_env)
		err_msg(NULL, "init");
	gen.env = env_init(start_env);
	if (!gen.env)
		err_msg(NULL, "init");
	gen.path = NULL;
	gen.status = 0;
	minishell_loop(&gen);
	exit(0);
}
