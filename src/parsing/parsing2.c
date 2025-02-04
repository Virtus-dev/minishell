/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2025/02/04 13:36:30 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_redir(t_data *data)
{
	int	pipe_num;
	/*
	 En este punto parseamos los datos para poder trabajar con los mismos,
	 y realizando el control de errores. ft_parse() ¿?
	*/
	check_input(data->input);

	// tokenizo el input.
	pipe_num = ft_count_pipes(data);
	data->tokens = tokenize_command(data->input);
	ft_pipe_processing(data, pipe_num);
}

int	ft_is_all_space(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (FALSE);
		i++;
	}
	data->status = 127;
	return (TRUE);
}

int	ft_count_pipes(t_data *data)
{
	int i;
	int pipes;
	
	i = 0;
	pipes = 0;
	while(data->input[i])
	{
		printf("input[%d] = %c\n", i, data->input[i]);
		if(data->input[i] == '|')
			pipes++;
		i++;
	}
	return(pipes);
}