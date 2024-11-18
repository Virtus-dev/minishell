/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2024/11/17 12:43:20 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_data *data)
{
	char	*argv_dup;

	if (!data->argv[1])
	{
		ft_putchar_fd('\n', data->fdout);
		return ;
	}
	if (!ft_flag_exist(data->argv[1]))
	{
		ft_putstr_fd(data->argv[1], data->fdout);
		ft_putchar_fd('\n', data->fdout);
	}
	else
	{
		argv_dup = ft_strdup(data->argv[1]);
		argv_dup = ft_chrignore(argv_dup, '\n');
		ft_putstr_fd(argv_dup, data->fdout);
		free (argv_dup);
	}
}
