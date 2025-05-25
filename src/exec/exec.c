/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/23 01:05:42 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	ft_signal_handler(t_data *data, int stat)
{
	if (WIFEXITED(stat))
		data->status = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 18);
			write(1, "\n", 1);
		}
		data->status = 128 + WTERMSIG(stat);
	}
}
*/
void	ft_exec(t_data *data)
{
	printf("Enft_exec\n");
	g_block = 1;
	if (data->env->keys[0] != NULL)
		ft_execpath(data);
	ft_runexec(data, NULL, data->fdin, data->fdout);
	g_block = 0;
}
