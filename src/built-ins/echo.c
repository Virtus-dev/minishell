/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/12 19:09:42 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_data *data)
{
	/*int	i;
	int	nl;
	
	i = 1;
	nl = 1;
	if (data->argv[i] && !ft_flag_exist(data->argv[i]))
	{
		nl = 0;
		i++;
	}*/
	int x = 0;
	while (data->argv[x])
	{
		printf("ARG[%d]: %s\n", x, data->argv[x]);
		x++;
	}
	/*while (data->argv[i])
	{
		ft_putstr_fd(data->argv[i], data->fdout);
		if (data->argv[i + 1])
		{
			ft_putstr_fd(" ", data->fdout);
			i++;
		}
		if(nl)
			ft_putchar_fd('\n', data->fdout);
	}*/
}
