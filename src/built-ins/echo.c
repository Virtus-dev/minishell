/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/05 19:01:26 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_data *data)
{
	char	*argv_dup;
	char	*expandable_var;

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
		if (ft_is_expandable(argv_dup))
		{
			expandable_var = ft_chrignore(argv_dup, '$');
			ft_putstr_fd(ft_getvar(data->exp, expandable_var), data->fdout);
			free(expandable_var);
		}
		else
		{
			ft_putstr_fd(argv_dup, data->fdout);
			free (argv_dup);
		}
	}
}
