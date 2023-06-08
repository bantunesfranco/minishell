/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_here_doc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:58:04 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/08 14:40:44 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_here_doc(char *delimiter)
{
	char	*line;
	char	*tmp;
	char	*str;

	errno = 0;
	line = NULL;
	str = ft_strdup("");
	if (!str)
		err_msg(NULL, "here_doc");
	while (1)
	{
		line = readline("> ");
		if (line == NULL && errno == ENOMEM)
			err_msg(NULL, "here_doc");
		else if (line == NULL && errno == 0)
			return (str);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		tmp = line;
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		if (line == NULL)
			err_msg(NULL, "here_doc");
		str = ft_strjoin_free(tmp, line);
		free(tmp);
		if (!str)
			err_msg(NULL, "here_doc");
	}
	return (str);
}

int	main(void)
{
	char	*str;

	str = read_here_doc("EOF");
	printf("str: %s\n", str);
	return (0);
}