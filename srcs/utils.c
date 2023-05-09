/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:07:05 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/09 17:07:57 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_valid_input(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (0);
		if (str[i] == '+' && str[i + 1] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	err_msg_exit(char *msg, char *msg2, char *msg3)
{
	write(2, "minishell: ", 11);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
	}
	if (errno == 127)
	{
		write(2, msg3, ft_strlen(msg3));
		write(2, ": command not found\n", 21);
	}
	else
		perror(msg3);
	exit(errno);
}
