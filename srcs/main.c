/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:01:01 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/30 14:53:59 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

void	executor(t_gen *gen, t_pipeline *pipeline)
{
	t_cmd	*cmd;
	int		id;
	int		status;
	int		i;

	id = fork();
	cmd = pipeline->first_cmd;
	gen->path = find_path(cmd->cmd, gen->env);
	i = check_access(gen, cmd);
	if (i == 1)
		return (printf("NO!!!\n"), exit(1));
	if (id == 0)
	{
		execve(cmd->path, cmd->cmd, gen->env);
		err_msg(NULL, cmd->cmd[0]);
		exit(errno);
	}
	else
		waitpid(id, &status, 0);
	// if (WIFEXITED(status))
	// 	exit(WEXITSTATUS(status));
	// exit(1);
}


void	minishell_loop(t_gen *gen)
{
	char		*line;
	char		*line2;
	t_pipeline	*input;

	(void)gen;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			line = readline("minishell$ ");
			if (line == NULL)
				err_msg(NULL, "line");
			if (ft_strlen(line))
				add_history(line);
		}
		else
		{
			line2 = get_next_line(STDIN_FILENO);
			if (line2 == NULL)
				err_msg(NULL, "line");
			line = ft_strtrim(line2, "\n");
			free(line2);
		}
		input = parse_line(line);
		free(line);
		if (input == NULL)
			printf("Syntax error\n");
		executor(gen, input);
		input++;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_gen	gen;
	char	**start_env;

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
	minishell_loop(&gen);
	exit(0);
}
