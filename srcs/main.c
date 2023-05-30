/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:01:01 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/30 12:36:56 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	minishell_loop(t_gen *gen)
{
	char		*line;
	char		*line2;
	t_pipeline	*lol;

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
		lol = parse_line(line);
		if (lol == NULL)
			printf("Syntax error\n");
		free(line);
		lol++;
		// printf("%s\n", line);
		// input_arr = ft_split_args(line, '|');
		// if (!input_arr)
		// 	ft_error("minishell: ", ENOMEM);
		// print_array(input_arr);
		// printf("\n");
		// ft_free_arr(input_arr);
		// input_arr = NULL;
	}
	// printf("\ndone\n\n");
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
