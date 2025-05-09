/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/09 11:53:08 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_block;

void	ft_minishell_init(t_data *data)
{
	while (1)
	{
		ft_setup_parent_signals();
		data->input = readline("$minishell>");
		if (data->input == NULL)
		{
			ft_exit(data);
			//escribir exit\n
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if (!ft_is_all_space(data->input, data))
			{
				ft_check_redir(data);
				free_tokens(data->tokens);
				data->tokens = NULL;
				ft_free_matrix(data->argv);
				data->argv = NULL;

			}
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