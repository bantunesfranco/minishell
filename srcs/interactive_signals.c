/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interactive_signals.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 19:00:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/23 14:42:44 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <termios.h>

void	sig_quit_handler_interactive(int signal)
{
	(void)signal;
	rl_redisplay();
}

void	sig_int_handler_interactive(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	// rl_done = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal_handlers_and_terminal_interactive(void)
{
	unset_echoctl();
	signal(SIGQUIT, sig_quit_handler_interactive);
	signal(SIGINT, sig_int_handler_interactive);
}
