/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:07:58 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/27 10:58:34 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Error control, checks if the argument passed by, its a number.
 * 
 * @param t_data Structure wich holds all the information.
 */
void    ft_check_exit(t_data *data)
{
    //if (data->argv[2])
    //    return (1);
    if (!ft_atoi(data->argv[1]))
    {
        ft_putstr_fd(data->argv[0], data->fdout);
        ft_putchar_fd('\n', data->fdout);
        ft_free_resources(data);
        exit(EXIT_FAILURE);
    }
    if (ft_isnumeric(data->argv[1]))
    {
		ft_putstr_fd(data->argv[0], data->fdout);
		ft_putchar_fd('\n', data->fdout);
		ft_putstr_fd("bash: ", data->fdout);
		ft_putstr_fd(data->argv[0], data->fdout);
		ft_putstr_fd(": ", data->fdout);
		ft_putstr_fd(data->argv[1], data->fdout);
		ft_putstr_fd(": numeric argument is required\n", data->fdout);
		ft_free_resources(data);
		exit(EXIT_FAILURE);
    }
}

void    ft_exit(t_data *data)
{
    if (data->argv[1])
        ft_check_exit(data);
    if (data->lvl > 1)
    {
        ft_putstr_fd("exiting..", data->fdout);
        data->lvl -= 1;
    }
    else
    {
        ft_putstr_fd("exit", data->fdout);
        ft_putchar_fd('\n', data->fdout);
        ft_free_resources(data);
        exit(EXIT_SUCCESS);
    }
}
