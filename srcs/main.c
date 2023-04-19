/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/19 15:37:09 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	char	**input_arr;
	int		i;

	while (1)
	{
		i = 0;
		line = readline("minishell$ ");
		if (!ft_strrchr(line, '\n'))
			printf("No nl\n");
		input_arr = ft_split_args(line, '|');
		if (!input_arr)
			ft_error("minishell: ", ENOMEM);
		printf("\n");
		while (input_arr[i])
		{
			printf("%s\n", input_arr[i]);
			i++;
		}
		printf("\n");
		ft_free_arr(input_arr);
		input_arr = NULL;
	}
	exit(0);
}
