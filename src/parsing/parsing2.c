/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2025/05/06 18:48:04 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*ft_epur(char *str)
{
	int		i;
	int		j;
	char	*c_input;

	i = 0;
	j = 0;
	c_input = ft_calloc(256, sizeof(char));
	while(str[i] != '\0')
	{
		if (str[i] && (str[i] == ' ' || str[i] == '\t'))
		{
			c_input[j] = str[i];
			j++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
		}
		c_input[j] = str[i];
		j++;
		i++;
	}
	j++;
	return (c_input);
}

void	ft_check_redir(t_data *data)
{
	int		pipe_num;
	char	*c_input;
	char	*c_input2;

	check_input(data->input);
	pipe_num = ft_count_pipes(data);
	c_input = ft_strtrim(data->input, " ");
	//trimear, acortar espacios de data->input y luego entrar en tokenizer
	data->tokens = tokenize_command(tokenizer(c_input));
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
