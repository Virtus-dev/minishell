/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by arigonza          #+#    #+#             */
/*   Updated: 2025/01/16 11:50:17 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_data *data)
{
	int	stat;
	
	data->child = fork();
	if (data->child == -1)
	{
		perror("FORK FAILURE");
		exit(EXIT_FAILURE);
	}
	if (ft_builtin_check(data->argv[0]) == DEF)
		data->lvl += 1;
	if (data->child == 0)
	{
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
