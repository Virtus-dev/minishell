/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:06:17 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/20 12:29:31 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

/**
 * @brief When the user presses CTRL+C
 * (which sends the SIGINT signal),
 * this function is called.
 * It clears the current input line, prints a newline, and 
 * refreshes the prompt so the user can enter a new command.
 * 
 * @param sig 
 */
void	ft_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Refresh the prompt and input line
 * when a signal (like SIGINT) is received
 * in a child process. It’s a minimal handler
 * that ensures the input state remains consistent.
 * 
 * @param sig 
 */
void	ft_child_handler(int sig)
{
	(void)sig;
	rl_redisplay();
}

/* Helper function to set signal handler */
static int	ft_set_signal(int sig, void (*handler)(int))
{
	struct sigaction sa;

	if (sigemptyset(&sa.sa_mask) == -1)
	{
		perror(SIGEMPT_ERR);
		return (-1);
	}
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(sig, &sa, NULL) == -1)
	{
		perror(SIGA_ERR);
		return (-1);
	}
	return (0);
}

static void	ft_ignore_signals(void)
{
	if (ft_set_signal(SIGQUIT, SIG_IGN) == -1)
	{
		perror(SIGIGN_ERR);
	}
}

// Set signal handlers for the main process
void	ft_signal(void)
{
	ft_ignore_signals();

	if (ft_set_signal(SIGINT, &ft_handler) == -1)
	{
		perror(SETINT_ERR);
	}
}

// Set signal handlers for child processes
void	ft_child_signal(void)
{
	if (ft_set_signal(SIGINT, &ft_child_handler) == -1)
	{
		perror(SETINT_CHLD);
	}

	if (ft_set_signal(SIGQUIT, &ft_child_handler) == -1)
	{
		perror(SETIGN_CHLD);
	}
}
