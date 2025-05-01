/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:14:16 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/01 09:29:48 by arigonza         ###   ########.fr       */
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
	if (i == pipe_num)
		data->fdout = STDOUT_FILENO;
	else
		data->fdout = fd[1];
	if (i == 0 && (ft_is_sin(data->input) || ft_is_din(data->input)))
		ft_start_redi(data);
	if (i == pipe_num && (ft_is_sout(data->input) || ft_is_dout(data->input)))
		ft_start_redi(data);
	close(fd[1]);
	if (i == 0 && (ft_is_sin(data->input) || ft_is_din(data->input)))
		close(fd[0]);
	else
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
	t_token	*curr_token;
	t_token	*next_token;

	i = 0;
	while (i <= pipe_num)
	{
		curr_token = data->tokens[i];
		next_token = data->tokens[i + 1];
		if (!curr_token || !curr_token->cmd)
		{
			perror("Command token not found\n");
			break ;
		}
		ft_load_args(data, curr_token);
		ft_clean_and_replace_args(data);
		ft_swapfd(data, i, pipe_num);
		if (ft_nonenv_builtin(curr_token->cmd) || (ft_is_env_builtin(curr_token->cmd) && !next_token))
			ft_exec_built(data, curr_token->cmd);
		else
			ft_exec(data);
		i++;
	}
	ft_close_fds(data);
}
