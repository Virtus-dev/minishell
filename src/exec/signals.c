/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:06:17 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/09 12:09:26 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <signal.h>

static void	sigint_parent(int sig)
{
	(void)sig;
	if (!g_block)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_block)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_setup_parent_signals(void)
{
	struct sigaction sa;

	sigaction(SIGQUIT, &(struct sigaction){ .sa_handler = SIG_IGN }, NULL);
	sa.sa_handler = sigint_parent;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags   = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	ft_restore_default_signals(void)
{
	signal(SIGINT,  SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
