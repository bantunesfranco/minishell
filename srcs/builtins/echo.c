/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:34:50 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/31 18:03:52 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	option_check(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->cmd[i])
	{
		j = 1;
		if (cmd->cmd[i][0] == '-')
		{
			if (cmd->cmd[i][1] != 'n')
				return (i);
			while (cmd->cmd[i][j] && cmd->cmd[i][j] == 'n')
			{
				j++;
				if (cmd->cmd[i][j] && cmd->cmd[i][j] != 'n')
					return (i);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

static int	write_content(char *content, int fd, int opt)
{
	if (!content || ft_strlen(content) == 0)
	{
		if (opt)
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
		if (opt)
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
	int		opt;
	int		pos;
	int		len;
	int		i;
	char	*str;

	(void)gen;
	opt = 0;
	pos = option_check(cmd);
	if (pos != 1)
		opt = 1;
	len = 0;
	i = pos;
	while (cmd->cmd[i])
	{
		len += (ft_strlen(cmd->cmd[i]) + 1);
		i++;
	}
	str = join_message(&cmd->cmd[pos], len);
	if (!str)
		return (err_msg(NULL, cmd->cmd[0]), -1);
	if (write_content(str, cmd->output->fd, opt) == -1)
		return (free(str), err_msg(cmd->cmd[0], "write error"), -1);
	return (free(str), 0);
}
