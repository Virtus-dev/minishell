/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/23 17:40:35 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	
	data = ft_init_data(argc, argv, env);
	while (1)
	{
		data->input = readline("Waiting for instructions...\n");
		if (data->input == NULL)
		{
			ft_putstr_fd("QUITTING MINISHELL\n", data->fdout);
			break;
		};
		if (!ft_strcmp(data->input, "pwd"))
			ft_pwd(data);
		if (!ft_strcmp(data->input, "cd"))
			ft_cd(data, data->input);
		if (!ft_strcmp(data->input, "echo"))
			ft_echo(data);
		if (!ft_strcmp(data->input, "env"))
			ft_env(data);
	}
	free(data->input);
	clear_history();
	return (FALSE);
}
