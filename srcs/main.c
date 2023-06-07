/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:01:01 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/07 20:49:54 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

char	*read_tty(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line == NULL && errno == ENOMEM)
		err_msg(NULL, "line");
	else if (line == NULL && errno == 0)
	{
		// rl_replace_line("exit", 0);
		if (write(STDOUT_FILENO, "exit\n", 5) == -1)
			err_msg(NULL, "write");
		exit(0);
	}
	if (ft_strlen(line))
		add_history(line);
	return (line);
}

char	*read_no_tty(void)
{
	char	*line;
	char	*line2;

	line2 = get_next_line(STDIN_FILENO);
	if (line2 == NULL)
		err_msg(NULL, "line");
	else if (line2 == NULL && errno == 0)
	{
		if (write(STDOUT_FILENO, "exit\n", 5) == -1)
			err_msg(NULL, "write");
		exit(0);
	}
	line = ft_strtrim(line2, "\n");
	free(line2);
	return (line);
}

t_pipeline	*goto_close_operator(t_pipeline *tmp)
{
	int		open;
	int		close;
	
	open = 1;
	close = 0;
	while (tmp && open - close != 0)
	{
		tmp = tmp->next;
		if (!tmp)
			break ;
		if (tmp->next_control_operator == OPEN)
			open++;
		if (tmp->next_control_operator == CLOSE)
			close++;
	}
	if (tmp && tmp->next_control_operator == CLOSE)
		tmp = tmp->next;
	return (tmp);
}

t_pipeline	*check_control_operators(t_gen *gen, t_pipeline *tmp)
{
	if (tmp->prev_control_operator == AND && gen->status != 0)
	{
		while (tmp)
		{
			if (tmp->next && tmp->next_control_operator == OPEN)
				tmp = goto_close_operator(tmp->next);
			else
				tmp = tmp->next;
			if (tmp && tmp->prev_control_operator == CLOSE)
				break ;
		}
	}
	else if (tmp->prev_control_operator == OR && gen->status == 0)
	{
		while (tmp)
		{
			if (tmp->next && tmp->next_control_operator == OPEN)
				tmp = goto_close_operator(tmp->next);
			else
				tmp = tmp->next;
			if (tmp && tmp->prev_control_operator == CLOSE)
				break ;
		}
	}
	return (tmp);
}

void	minishell_loop(t_gen *gen)
{
	t_pipeline	*input;
	t_pipeline	*tmp;
	char		*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = read_tty();
		else
			line = read_no_tty();
		input = parse_line(line, gen);
		free(line);
		tmp = input;
		while (tmp)
		{
			executor(gen, tmp);
			if (tmp->next)
				tmp = check_control_operators(gen, tmp->next);
			else
				break ;
		}
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
