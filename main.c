/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2025/03/14 12:07:19 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		data->input = readline("HI MINISHELL\n");
		ft_set_signal();
		if (data->input == NULL)
		{
			ft_putstr_fd(BAD_INPUT, data->fdout);
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			/*if (check_quotes(data->input))
			{
				ft_putstr_fd("You must close quotes\n", data->fdout);
				data->status = 1;
			}
			*/
			if (!ft_is_all_space(data->input, data))
				ft_check_redir(data);
			//printf("%s\n", data->argv[i]);
		}
		free(data->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	(void)argv;
	
	using_history();
	data = ft_init_data(argc, env);
	ft_minishell_init(data);
	ft_free_resources(data);
	free(data);
	return (0);
}