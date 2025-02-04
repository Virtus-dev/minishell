/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:06:17 by arigonza          #+#    #+#             */
/*   Updated: 2025/02/02 13:00:14 by arigonza         ###   ########.fr       */
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

int	ft_set_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ft_child_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (EXIT_SUCCESS);
}

void	ft_ignore_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_signal(void)
{
	struct sigaction	sa;
	
	ft_ignore_signals();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ft_handler;
	sigaction(SIGINT, &sa, NULL);
}

