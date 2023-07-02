/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:01:01 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/02 19:16:16 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

void	execute_instructions(t_gen *gen, t_pipeline *input);

char	*read_tty(t_gen *gen)
{
	char	*line;

	line = readline("\033[1;35mminishell$ \033[0m");
	if (line == NULL && errno == ENOMEM)
		err_msg(NULL, "line");
	else if (line == NULL && errno == 0)
	{
		if (write(STDOUT_FILENO, "exit\n", 5) == -1)
			err_msg(NULL, "write");
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
		err_msg(NULL, "line");
	else if (line2 == NULL && errno == 0)
	{
		// if (write(STDOUT_FILENO, "exit\n", 5) == -1)
		// 	err_msg(NULL, "write");
		set_echoctl();
		exit(gen->status);
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
		tmp = tmp->next->next;
	return (tmp);
}

t_pipeline	*check_control_operators(t_gen *gen, t_pipeline *tmp)
{
	if (tmp->prev_control_operator == CLOSE || tmp->prev_control_operator == OPEN)
		return (tmp);
	while (tmp)
	{
		if (tmp->prev_control_operator == AND && gen->status == 0)
			return (tmp);
		else if (tmp->prev_control_operator == OR && gen->status != 0)
			return (tmp);
		else if (tmp->next && tmp->next_control_operator == OPEN)
			tmp = goto_close_operator(tmp);
		else
			tmp = tmp->next;
		if (tmp && tmp->prev_control_operator == CLOSE)
			break ;
	}
	return (tmp);
}

int	execute_pipeline(t_gen *gen, t_pipeline **pipeline, int *pipe_read)
{
	int	id;
	int	p[2];

	if ((*pipeline)->next_control_operator == PIPE)
	{
		if (pipe(p) == -1)
		{
			err_msg(NULL, "executor");
			return (-1);
		}
	}
	else
	{
		p[0] = -1;
		p[1] = -1;
	}
	id = fork();
	if (id == -1)
	{
		err_msg(NULL, "executor");
		return (-1);
	}
	else if (id == 0)
	{
		if ((*pipeline)->next_control_operator == PIPE)
		{
			close(p[0]);
			if (dup2(p[1], STDOUT_FILENO) == -1)
				child_err_msg(NULL, "executor");
			close(p[1]);
		}
		if ((*pipeline)->prev_control_operator == PIPE)
		{
			if (dup2(*pipe_read, STDIN_FILENO) == -1)
				child_err_msg(NULL, "executor");
			close(*pipe_read);
		}
		executor(gen, *pipeline);
		_exit(gen->status);
	}
	else
	{
		if ((*pipeline)->prev_control_operator == PIPE)
		{
			close(*pipe_read);
		}
		if ((*pipeline)->next_control_operator == PIPE)
		{
			close(p[1]);
			*pipe_read = p[0];
		}
		*pipeline = (*pipeline)->next;
	}
	return (id);
}

int	execute_subshell(t_gen *gen, t_pipeline **subshell, int *pipe_read)
{
	int	id;
	int	p[2];

	// printf("%d\n", (*subshell)->subshell->pipe_output);
	// printf("%d\n", (*subshell)->subshell->pipe_input);
	if ((*subshell)->subshell->pipe_output == 1)
	{
		if (pipe(p) == -1)
		{
			err_msg(NULL, "executor");
			return (-1);
		}
	}
	else
	{
		p[0] = -1;
		p[1] = -1;
	}
	id = fork();
	if (id == -1)
	{
		err_msg(NULL, "executor");
		return (-1);
	}
	else if (id == 0)
	{
		if ((*subshell)->subshell->pipe_output == 1)
		{
			close(p[0]);
			if (dup2(p[1], STDOUT_FILENO) == -1)
				child_err_msg(NULL, "executor");
			close(p[1]);
		}
		if ((*subshell)->subshell->pipe_input == 1)
		{
			if (dup2(*pipe_read, STDIN_FILENO) == -1)
				child_err_msg(NULL, "executor");
			close(*pipe_read);
		}
		// printf("%p\n", (*subshell)->subshell);
		// printf("fiss%p\n", (*subshell)->first_cmd);
		// // printf("%s\n", (*subshell)->first_cmd->cmd[0]);
		// printf("fz2%p\n", (*subshell)->next->first_cmd);
		// printf("%s\n", (*subshell)->next->first_cmd->cmd[0]);
		// printf("lololol%p\n", (*subshell)->next->subshell);
		execute_instructions(gen, (*subshell)->next);
		_exit(gen->status);
	}
	else
	{
		if ((*subshell)->subshell->pipe_input == 1)
		{
			close(*pipe_read);
		}
		if ((*subshell)->subshell->pipe_output == 1)
		{
			close(p[1]);
			*pipe_read = p[0];
		}
		*subshell = goto_close_operator(*subshell);
	}
	return (id);
}

t_pipeline	*execute_pipeline_list(t_gen *gen, t_pipeline *first_pipeline)
{
	t_pipeline	*tmp;
	int			id;
	int			pipe_read;

	pipe_read = 0;
	tmp = first_pipeline;
	while (tmp != NULL)
	{
		if (tmp->next_control_operator == OPEN)
		{
			// printf("here\n");
			id = execute_subshell(gen, &tmp, &pipe_read);
			// printf("tmp-%p\n", tmp->subshell);
		}
		else if (tmp->next_control_operator == PIPE || tmp->prev_control_operator == PIPE)
		{
			// printf("not\n"); 
			id = execute_pipeline(gen, &tmp, &pipe_read);
		}
		else
			break;
		// tmp = tmp->next;
	}
	waitpid(id, &gen->status, 0);
	if (WIFEXITED(gen->status))
	{
		gen->status = WEXITSTATUS(gen->status);
	}
	else if (WIFSIGNALED(gen->status))
		gen->status = 128 + WTERMSIG(gen->status);
	while (1)
		if (wait(NULL) == -1)
			break ;
	// printf("%p\n", tmp);
	// printf("%p\n", tmp->first_cmd);
	// printf("%s\n", tmp->first_cmd->cmd[0]);
	return (tmp);
}

void	execute_instructions(t_gen *gen, t_pipeline *input)
{
	t_pipeline *tmp;

	tmp = input;
	while (tmp != NULL)
	{
		if (tmp->prev_control_operator == CLOSE)
		{
			// printf("lol\n");
			break ;
		}
		else if (tmp->next_control_operator == OPEN || tmp->next_control_operator == PIPE)
		{
			// printf("huh\n");
			// printf("%d\n", tmp->next_control_operator);
			tmp = execute_pipeline_list(gen, tmp);
		}
		else
		{
			// printf("hi\n");
			executor(gen, tmp);
			tmp = tmp->next;
		}
		if (tmp)// && tmp->next)
		{
			tmp = check_control_operators(gen, tmp);
			// printf("%p\n", tmp);
		}
		else
		{
			// printf("aodkoasd\n");
			break ;
		}
	}
}

void	minishell_loop(t_gen *gen)
{
	t_pipeline	*input;
	t_pipeline	*tmp;
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
		tmp = input;
		// while (tmp)
		// {
			execute_instructions(gen, tmp);
			// executor(gen, tmp);
			// if (tmp->next)
			// 	tmp = check_control_operators(gen, tmp->next);
			// else
			// 	break ;
		// }
		// system("leaks -q minishell");
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
	// rl_getc_function = getc;
	if (argc != 1)
	{
		ft_putendl_fd("minishell: too many args", 2);
		return (1);
	}
	setup_signal_handlers_and_terminal_interactive();
	start_env = ft_arrdup(envp);
	if (!start_env)
		err_msg(NULL, "init");
	gen.env = env_init(start_env);
	if (!gen.env)
		err_msg(NULL, "init");
	gen.path = NULL;
	gen.status = 0;
	minishell_loop(&gen);
	set_echoctl();
	exit(gen.status);
}
