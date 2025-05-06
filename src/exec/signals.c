/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:06:17 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/06 13:43:12 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <signal.h>

static void	sigint_parent(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    // if la variable global no esta en modo bloqueante
        //rl_redisplay();
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
