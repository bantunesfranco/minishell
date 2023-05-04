/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:34:50 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/04 10:05:03 by bruno         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static int	option_check(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-')
	{
		if (cmd->cmd[1][1] != 'n')
			return (0);
		while (cmd->cmd[1][i] && cmd->cmd[1][i] == 'n')
		{
			i++;
			if (cmd->cmd[1][i] && cmd->cmd[1][i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

static int	write_content(char *content, int fd, int option)
{
	if (!content || ft_strlen(content) == 0)
	{
		if (option)
		{
			if (write(fd, "\0", 1) == -1)
				return (-1);
		}
		else
		{
			if (write(fd, "\n", 1) == -1)
				return (-1);
		}
	}
	else
	{
		if (write(fd, content, ft_strlen(content)) == -1)
			return (-1);
		if (option)
			return (0);
		if (write(fd, "\n", 1) == -1)
			return (-1);
	}
	return (0);
}

static char	*join_message(char **args, int len)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	if (len == 0)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i] && j < len)
	{
		size = ft_strlen(args[i]);
		ft_memmove(&str[j], args[i], size);
		j += size;
		if (j == len - 1)
			str[j] = '\0';
		else
			str[j] = ' ';
		j++;
		i++;
	}
	return (str);
}

int	echo(t_gen *gen, t_cmd *cmd)
{
	int		option;
	int		args;
	int		len;
	int		i;
	char	*str;

	(void)gen;
	option = option_check(cmd);
	if (option == 1)
		args = 2;
	else
		args = 1;
	len = 0;
	i = args;
	while (cmd->cmd[i])
	{
		len += (ft_strlen(cmd->cmd[i]) + 1);
		i++;
	}
	str = join_message(&cmd->cmd[args], len);
	if (write_content(str, cmd->output->fd, option) == -1)
		return (free(str), -1);
	free(str);
	return (0);
}
