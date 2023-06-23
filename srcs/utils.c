/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:07:05 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/23 10:02:45 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <termios.h>

int	ft_envcmp(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((s1[i] || s2[j]) && s1[i] == s2[j] && s1[i] != '=' && s2[j] != '=')
	{
		i++;
		j++;
		if (s2[j] == '+' && s2[j + 1] == '=' && s1[i] == '=')
			return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int	is_valid_input(char *str)
{
	int	i;

	i = 0;
	if ((!ft_isalnum(str[0]) && str[0] != '_' ) \
	|| (str[0] == '_' && str[1] == '\0'))
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

void	unset_echoctl(void)
{
	// struct termios	termios;

	// if (tcgetattr(0, &termios) == -1)
	// {
	// 	err_msg(NULL, "set echoctl");
	// 	return ;
	// }
	// termios.c_lflag &= ~ECHOCTL;
	// if (tcsetattr(0, 0, &termios) == -1)
	// 	err_msg(NULL, "set echoctl");
}

void	set_echoctl(void)
{
	// struct termios	termios;

	// if (tcgetattr(0, &termios) == -1)
	// {
	// 	err_msg(NULL, "unset echoctl");
	// 	return ;
	// }
	// termios.c_lflag |= ECHOCTL;
	// if (tcsetattr(0, 0, &termios) == -1)
	// 	err_msg(NULL, "unset echoctl");
}
