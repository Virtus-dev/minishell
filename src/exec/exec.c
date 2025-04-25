/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/25 09:33:39 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Comprobar el manejo de señales aqui con bloqueantes
//Manejo de $?
void	ft_exec(t_data *data)
{
	int	stat;

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
