/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2025/01/28 22:58:31 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


void    ft_minishell_init(t_data *data)
{
    while (1)
	{
		ft_signal();
		data->input = readline("HI MINISHELL");
		ft_set_signal();
		if (data->input == NULL)
		{
			ft_putstr_fd(BAD_INPUT, data->fdout);
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if (check_quotes(data->input))
			{
				ft_putstr_fd("You must close quotes\n", data->fdout);
				data->status = 1;
			}
			else if (!ft_is_all_space(data->input, data))
				ft_check_redir(data);
		}
		free(data->input);
	}
}