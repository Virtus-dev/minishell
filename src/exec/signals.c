/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:06:17 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/21 13:23:41 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <signal.h>

// parent_signals.c
static void	sigint_parent(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	ft_setup_parent_signals(void)
{
    struct sigaction sa;

    /* Ignorar SIGQUIT */
    sigaction(SIGQUIT, &(struct sigaction){ .sa_handler = SIG_IGN }, NULL);

    /* Capturar SIGINT */
    sa.sa_handler = sigint_parent;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags   = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
}

// child_signals.c
void	ft_restore_default_signals(void)
{
    signal(SIGINT,  SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
