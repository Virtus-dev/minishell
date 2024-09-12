/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/12 19:36:14 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	
	data = ft_init_data(argc, argv, env);
	printf("Press ctrl+D to exit\n");
	while ((data->input = readline(NULL)) != NULL)
	{
		if (data->input && data->input)
		{
			add_history(data->input);
		}
		if (!ft_strcmp(data->input, "pwd"))
			ft_pwd(data);
		if (!ft_strcmp(data->argv[0], "cd"))
			ft_cd(data);
	}
	free(data->input);
	clear_history();
	return (0);
}
