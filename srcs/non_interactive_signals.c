/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   non_interactive_signals.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 19:00:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/07 17:03:09 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <termios.h>
#include <readline/readline.h>

void	sig_quit_handler_non_interactive(int signal)
{
	(void)signal;
}

void	sig_int_handler_non_interactive(int signal)
{
	(void)signal;
}

void	setup_signal_handlers_and_terminal_non_interactive(void)
{
	set_echoctl();
	signal(SIGQUIT, sig_quit_handler_non_interactive);
	signal(SIGINT, sig_int_handler_non_interactive);
}
