/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   non_interactive_signals.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 19:00:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/21 18:42:52 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <termios.h>
// #include <term.h>
// #include <curses.h>

int	put_char(int lol)
{
	return (write(1, &lol, 1));
}

void	heredoc_handler(int signal)
{
	(void)signal;
	g_kill_switch = 1;
	// rl_done = 1;
	// rl_line_buffer = NULL;
	// tputs(clear_screen, 1, put_char);
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
