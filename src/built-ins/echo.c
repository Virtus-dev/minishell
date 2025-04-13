/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 13:23:10 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void ft_echo(t_data *data)
{
	int	i;
	int	nl;
	
	i = 1;
	nl = 1;
	if (data->argv[i] && !ft_flag_exist(data->argv[i]))
	{
		nl = 0;
		i++;
	}
	int x = 0;
	while (data->argv[x])
	{
		printf("ARG[%d]: %s\n", x, data->argv[x]);
		x++;
	}
	while (data->argv[i])
	{
		ft_putstr_fd(data->argv[i], data->fdout);
		if (data->argv[i + 1])
		{
			ft_putstr_fd(" ", data->fdout);
			i++;
		}
		if(nl)
			ft_putchar_fd('\n', data->fdout);
	}
}
*/

void ft_echo(t_data *data)
{
    char    *argv_dup;
    char    *expandable_var;
    char    *var;

    if (!data->argv[1])
    {
        ft_putchar_fd('\n', data->fdout);
        return ;
    }
    if (!ft_flag_exist(data->argv[1]))
    {
        if (ft_is_expandable(data->argv[1]))
        {
            argv_dup = ft_strdup(data->argv[1]);
            expandable_var = ft_chrignore(argv_dup, '$');
            var = ft_getvar(data->exp, expandable_var);
            if (!var)
                return ;
            ft_putstr_fd(var, data->fdout);
            free(expandable_var);
        }
        else
            ft_putstr_fd(data->argv[1], data->fdout);
        ft_putchar_fd('\n', data->fdout);
    }
    else
    {
        argv_dup = ft_strdup(data->argv[2]);
        argv_dup = ft_chrignore(argv_dup, '\n');
        ft_putstr_fd(argv_dup, data->fdout);
        free(argv_dup);
    }
}
