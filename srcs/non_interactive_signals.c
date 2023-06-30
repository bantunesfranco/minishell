/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   non_interactive_signals.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 19:00:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/30 13:42:09 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <termios.h>
#include <readline/readline.h>

void	heredoc_handler(int signal)
{
	(void)signal;
	// g_kill_switch = 1;
	// rl_line_buffer = NULL;
	// rl_on_new_line();
	// rl_replace_line(str , 0);
	// rl_redisplay();
	// write(0, "\n", 2);
}

void	sig_quit_handler_non_interactive(int signal)
{
	(void)signal;
	write(0, "Quit: 3\n", 8);
}

void	sig_int_handler_non_interactive(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	setup_signal_handlers_and_terminal_non_interactive(void)
{
	set_echoctl();
	signal(SIGQUIT, sig_quit_handler_non_interactive);
	signal(SIGINT, sig_int_handler_non_interactive);
}
