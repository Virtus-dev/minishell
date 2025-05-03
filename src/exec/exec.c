/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/03 23:40:33 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_father_exit(t_data *data)
{
	if (!data || data->argv || !data->argv[0])
		return (0);
	if (ft_strcmp(data->argv[0], "exit") == 0)
	{
		ft_exit(data);
		return (1);
	}
	return (0);
}

void	ft_exec(t_data *data)
{
	int	stat;

	if (ft_father_exit(data))
		return ;
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
		if (WIFEXITED(stat))
			data->status = WEXITSTATUS(stat);
	}
	else
		perror(FORK_ERR);
}
