/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:34:50 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/20 12:01:32 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str, char *option)
{
	if (!str || ft_strlen(str) == 0)
	{
		if (!option)
			write(1, "\n", 1);
		else
			write(1, "\0", 1);
	}
	else if (option)
	{
		if (write(1, str, ft_strlen(str)) == -1)
			ft_error("minishell: ", errno);
	}
	else
	{
		if (write(1, str, ft_strlen(str)) == -1)
			ft_error("minishell: ", errno);
		if (write(1, "\n", 1) == -1)
			ft_error("minishell: ", errno);
	}
	exit(0);
}
