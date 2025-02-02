/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2025/02/02 12:51:27 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_redir(t_data *data)
{
	/*
	 En este punto parseamos los datos para poder trabajar con los mismos,
	 y realizando el control de errores. ft_parse() ¿?
	*/

	// tokenizo el input.
	data->tokens = tokenize_command(data->input);
	ft_pipe_processing(data, ft_count_pipes(data));
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

int	ft_countpipes(t_data *data)
{
	char *input;
	int i;
	int pipes;
	i = 0;
	input = ft_strdup(t_data->input);
	while(input[i])
	{
		if(input[i] == "|")
			pipes++;
		i++;
	}
	return(pipes);
}