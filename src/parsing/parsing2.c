/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2025/04/17 15:57:45 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_redir(t_data *data)
{
	int	pipe_num;

	check_input(data->input);
	pipe_num = ft_count_pipes(data);
	data->tokens = tokenize_command(tokenizer(data->input));
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
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (data->input[i])
	{
		if (data->input[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}
