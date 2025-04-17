/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 15:48:21 by fracurul         ###   ########.fr       */
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
		ft_execpath(data);
		//Implementar ruta absoluta sin path
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
