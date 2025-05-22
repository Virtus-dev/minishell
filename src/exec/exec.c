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

void	ft_exec(t_data *data)
{
	int	stat;

	g_block = 1;
	data->child = fork();
	if (data->child == -1)
	{
		perror(FORK_ERR);
		exit(EXIT_FAILURE);
	}
	if (data->child == 0)
	{
		ft_restore_default_signals();
		if (data->env->keys[0] != NULL)
			ft_execpath(data);
		ft_runexec(data, NULL, 0, 0);
	}
	else if (data->child > 0)
	{
		waitpid(data->child, &stat, WUNTRACED);
		ft_signal_handler(data, stat);
	}
	else
		perror(FORK_ERR);
	g_block = 0;
}
