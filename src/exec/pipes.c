/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:14:16 by arigonza          #+#    #+#             */
/*   Updated: 2025/02/09 14:43:56 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swapfd(t_data *data, int i, int pipe_num)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror(PIPE_ERR);
		return ;
	}
	if (pipe_num == i)
	{
		data->fdout = STDOUT_FILENO;
		ft_start_redi(data);
		close(fd[0]);
	}
	else
	{
		data->fdout = fd[1];
		ft_start_redi(data);
	}
	close(fd[1]);
	data->fdin = fd[0];
}

void	ft_close_fds(t_data *data)
{
	if (data->fdin != STDIN_FILENO)
		close(data->fdin);
	if (data->fdout != STDOUT_FILENO)
		close(data->fdout);
	data->fdin = STDIN_FILENO;
	data->fdout = STDOUT_FILENO;
}

void	ft_pipe_processing(t_data *data, int pipe_num)
{
	int		i;
	int		toklen;
	t_token	*curr_token;

	i = 0;
	toklen = ft_toklen(data->tokens);
	printf("TOKLEN = %d\n", toklen);
	while (i <= pipe_num)
	{
		curr_token = data->tokens[i];
		printf("currnt_token = %s\n", curr_token->cmd);
		if (!curr_token || !curr_token->cmd)
		{
			perror("Command token not found\n");
			break;
		}
		ft_load_args(data, curr_token);
		ft_swapfd(data, i, pipe_num);
		if (ft_builtin_check(curr_token->cmd))
			ft_exec_built(data, curr_token->cmd);
		else
			ft_exec(data);
		i++;
	}
	ft_close_fds(data);
}
