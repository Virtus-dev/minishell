/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/09 12:08:15 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_runexec(data);
	}
	else if (data->child > 0)
	{
		waitpid(data->child, &stat, WUNTRACED);
		g_block = 0;
		if (WIFEXITED(stat))
			data->status = WEXITSTATUS(stat);
	}
	else
		perror(FORK_ERR);
}
