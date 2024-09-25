/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/25 20:09:47 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_data *data)
{
	int	stat;
	
	data->child = fork();
	if (ft_builtin_check(data->argv[0]) == DEF)
		data->lvl += 1;
	if (data->child == 0)
		ft_execpath(data);
		ft_runexec(data);
	if(data->child < 0)
		data->status = 1;
	else
	{
		waitpid(data->child, &stat, WUNTRACED);
		if (data->child > 0)
		{
			if (WIFEXITED(stat))
				data->status = WEXITSTATUS(stat);
		}
	}
}