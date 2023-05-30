/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:07:05 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/29 12:56:58 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

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
