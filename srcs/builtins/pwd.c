/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:47:19 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/20 12:15:46 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_error("minishell: ", errno);
	if (write(1, path, ft_strlen(path)) == -1)
		ft_error("minishell: ", errno);
	if (write(1, "\n", 1) == -1)
		ft_error("minishell: ", errno);
	free(path);
	exit(0);
}
