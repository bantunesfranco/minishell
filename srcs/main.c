/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:01:01 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/04 19:09:11 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

char	*read_tty(t_gen *gen)
{
	char	*line;

	line = readline("\033[1;35mminishell$ \033[0m");
	if (line == NULL && errno == ENOMEM)
		err_msg(NULL, "read_input");
	else if (line == NULL && errno == 0)
	{
		if (write(STDOUT_FILENO, "exit\n", 5) == -1)
			err_msg(NULL, "write");
		rl_clear_history();
		set_echoctl();
		exit(gen->status);
	}
	if (line && ft_strlen(line))
		add_history(line);
	return (line);
}

char	*read_no_tty(t_gen *gen)
{
	char	*line;
	char	*line2;

	errno = 0;
	line2 = get_next_line(STDIN_FILENO);
	if (line2 == NULL && errno == ENOMEM)
		err_msg(NULL, "read_input");
	else if (line2 == NULL && errno == 0)
	{
		set_echoctl();
		exit(gen->status);
	}
	else if (line2 == NULL)
		return (NULL);
	line = ft_strtrim(line2, "\n");
	free(line2);
	if (line == NULL)
		err_msg(NULL, "read_input");
	return (line);
}

void	minishell_loop(t_gen *gen)
{
	t_pipeline	*input;
	char		*line;

	while (1)
	{
		setup_signal_handlers_and_terminal_interactive();
		if (isatty(STDIN_FILENO))
			line = read_tty(gen);
		else
			line = read_no_tty(gen);
		setup_signal_handlers_and_terminal_non_interactive();
		input = parse_line(line, gen);
		free(line);
		execute_instructions(gen, input);
		free_parsed_structs(input);
		errno = 0;
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
	setup_signal_handlers_and_terminal_interactive();
	if (!start_env)
		err_msg(NULL, "init");
	gen.env = env_init(start_env);
	if (!gen.env)
		err_msg(NULL, "init");
	gen.path = NULL;
	gen.status = 0;
	minishell_loop(&gen);
	set_echoctl();
	rl_clear_history();
	exit(gen.status);
}
