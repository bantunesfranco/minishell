/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 19:00:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/20 19:59:45 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <termios.h>

void	sig_quit_handler(int signal)
{
	(void)signal;
	rl_redisplay();
}

void	sig_int_handler(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}

void	setup_signal_handlers(void)
{
	struct termios	test;
	struct termios	test2;
	int	lol;

	lol = tcgetattr(0, &test);
	test2 = test;
	// printf("%d\n", lol);
	test2.c_lflag &= ~ECHOCTL;
	lol = tcsetattr(0, 0, &test2);
	// printf("%d\n", lol);
	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, sig_int_handler);
}
