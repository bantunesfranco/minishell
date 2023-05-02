/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/02 13:10:16 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	// char	**input_arr;
	int		i;
	t_cmd	*lol;
	(void)argc;
	(void)argv;
	(void)env;

	while (1)
	{
		i = 0;
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		lol = parse_line(line);
		// printf("%s\n", line);
		// input_arr = ft_split_args(line, '|');
		// if (!input_arr)
		// 	ft_error("minishell: ", ENOMEM);
		// print_array(input_arr);
		// printf("\n");
		// ft_free_arr(input_arr);
		// input_arr = NULL;
	}
	exit(0);
}

// int	main(int argc, char *argv[], char **env)
// {
// 	char	*path = "/Users/jmolenaa/Codam/Codam_unfinished/minihell/minishell/a.out";
// 	char	*cmd[] = {"a.out", NULL};
// 	(void)argc;
// 	(void)argv;
// 	(void)env;

// 	// printf("%d\n", execve(path, argv, env));
// 	char	*en[] = {"lol", "popopop", "asdasdasd", NULL};

// 	execve(path, cmd, en);
// 	// printf("%d\n", errno);
// 	// perror("hi");
// }
