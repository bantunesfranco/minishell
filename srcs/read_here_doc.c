/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_here_doc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:58:04 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/19 15:28:11 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
// #include "readline.h"

// static char	*read_loop(char *del, char *str)
// {
// 	char	*line;
// 	char	*tmp;

// 	errno = 0;
// 	str = ft_strdup("");
// 	if (!str)
// 		err_msg(NULL, "here_doc");
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line == NULL && errno == ENOMEM)
// 			err_msg(NULL, "here_doc");
// 		else if (line == NULL && errno == 0)
// 			return (str);
// 		if (!ft_strncmp(line, del, ft_strlen(del) + 1))
// 			break ;
// 		tmp = line;
// 		line = ft_strjoin(tmp, "\n");
// 		free(tmp);
// 		if (line == NULL)
// 			err_msg(NULL, "here_doc");
// 		str = ft_strjoin_free(str, line);
// 		if (!str)
// 			err_msg(NULL, "here_doc");
// 	}
// 	return (str);
// }

// static char	*skip_quotes(char *del, int qts)
// {
// 	char	*new_del;
// 	int		i;
// 	int		j;
// 	char	c;

// 	i = -1;
// 	c = 0;
// 	new_del = ft_calloc(ft_strlen(del) - qts + 1, sizeof(char));
// 	if (!new_del)
// 		err_msg(NULL, "here_doc");
// 	while (del[++i])
// 	{
// 		j = i;
// 		if (del[i] != '\'' && del[i] != '\"')
// 		{
// 			c =  del[i];
// 			while (del[i] && del[i] != c)
// 				j++;
// 		}
// 		ft_memcpy(new_del, del + j + 1 , j - i);
// 		if (del[i] == c)
// 			i++;
// 		i += j;
// 	}
// 	return (new_del);
// }

// char	*remove_quotes(char *del)
// {
// 	int		qts;
// 	int		i;
// 	char	c;

// 	i = 0;
// 	qts = 0;
// 	c = 0;
// 	while (del[i])
// 	{
// 		if (del[i] != '\'' && del[i] != '\"')
// 		{
// 			c =  del[i];
// 			qts += 2;
// 			i++;
// 			while (del[i] && del[i] != c)
// 				i++;
// 			if (del[i] == c)
// 				i++;
// 		}
// 		if (del[i])
// 			i++;
// 	}
// 	return (skip_quotes(del, qts));
// }

// char	*read_here_doc(char *delimiter)
// {
// 	char	*str;
// 	char	*new_delimiter;

// 	errno = 0;
// 	str = ft_strdup("");
// 	if (!str)
// 		err_msg(NULL, "here_doc");
// 	new_delimiter = remove_quotes(delimiter);
// 	printf("new_del: %s\n", new_delimiter);
// 	str = read_loop(new_delimiter, str);
// 	free(new_delimiter);
// 	return (str);
// }

// int	main(void)
// {
// 	char	*str;

// 	str = read_here_doc("\"EOF\"");
// 	// printf("%zd\n", write(1, "jtydjtyjty", 0));
// 	printf("str: %s", str);
// 	free(str);
// 	return (0);
// }
