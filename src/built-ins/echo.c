/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/17 12:53:45 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Franco, aqui hay que buscar una manera de sacar
 * el token correspondiente al token de echo.
 */
void ft_echo(t_data *data)
{
	char	*argv_dup;

	data->argv = data->token->str;
	if (!ft_flag_exist(data->argv[1]))
	{
		ft_putstr_fd(data->argv[1], data->fdout);
		ft_putchar_fd('\n', data->fdout);
	}
	else
	{
		// Aqui estoy sustituyendo de mala manera lo
		// que vendria a ser el tokken de echo.
		argv_dup = ft_strdup(data->argv[1]);
		argv_dup = ft_chrignore(argv_dup, '\n');
		ft_putstr_fd(argv_dup, data->fdout);
		free (argv_dup);
	}
	data->token = data->token->next;
}
