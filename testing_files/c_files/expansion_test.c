/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 15:07:27 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/03 17:07:34 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	t_gen	gen;
	char	**start_env;

	start_env = ft_arrdup(envp);
	gen.env = env_init(start_env);
	expand_environment_vars(argv[1], &gen);
}