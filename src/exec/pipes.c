/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:14:16 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/23 15:43:10 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_redirection(t_token *token)
{
	int	j;

	j = 0;
	while (token->cargs && token->cargs[j])
	{
		if (ft_redir_type(token->cargs[j]) != -1)
		{
			return (TRUE);
		}
		j++;
	}
	return (FALSE);
}

void	ft_swapfd(t_data *data, int i, int pipe_num)
{
	int		fd[2];
	//t_token	*token;

	if (pipe(fd) == -1)
	{
		perror(PIPE_ERR);
		return ;
	}
	//token = data->tokens[i];
	if (i == pipe_num)
		data->fdout = STDOUT_FILENO;
	else
		data->fdout = fd[1];
	close(fd[1]);
	if (i == 0)
		close(fd[0]);
	else
		data->fdin = fd[0];
	//printf ("fd_in = %d\nfd_out = %d\n", data->fdin, data->fdout);
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
/*
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
		if (ft_nonenv_builtin(curr_token->cmd)
		|| (ft_is_env_builtin(curr_token->cmd) && !next_token))
		ft_exec_built(data, curr_token->cmd);
		else if (!ft_builtin_check(curr_token->cmd))
			ft_exec(data);
		i++;
	}
	ft_close_fds(data);
}
*/

void	ft_child_process(t_data *data, t_token *curr, t_token *next)
{
	printf("DEBUG: cmd = %s\n", curr->cmd);
	printf("DEBUG: argv[0] = %s\n", data->argv[0]);
	ft_restore_default_signals();
	if (has_redirection(curr))
		ft_start_redi(data, curr);
	/*if (data->fdin != STDIN_FILENO)
		dup2(data->fdin, STDIN_FILENO);
	if (data->fdout != STDOUT_FILENO)
		dup2(data->fdout, STDOUT_FILENO);*/
	if (ft_nonenv_builtin(curr->cmd)
		|| (ft_is_env_builtin(curr->cmd) && !next))
		ft_exec_built(data, curr->cmd);
	else if (!ft_builtin_check(curr->cmd))
		ft_exec(data);
	exit(data->status);
}

void	ft_parent_cleanup(t_data *data)
{
	if (data->fdin != STDIN_FILENO)
		close(data->fdin);
	if (data->fdout != STDOUT_FILENO)
		close(data->fdout);
}

void	ft_pipe_processing(t_data *data, int pipe_num)
{
	int		i;
	//pid_t	pid;
	
	i = 0;
	while (i <= pipe_num)
	{
		ft_load_args(data, data->tokens[i]);
		ft_clean_and_replace_args(data);
		ft_swapfd(data, i, pipe_num);
		if (pipe_num == 0 && ft_builtin_check(data->tokens[i]->cmd) == EXIT)
		{
			ft_exec_built(data, data->tokens[i]->cmd);
			continue ;
		}
		data->child = fork();
		printf("PID = %d\nCMD = %s\n", data->child, data->tokens[i]->cmd);
		if (data->child == 0)
			ft_child_process(data, data->tokens[i], data->tokens[i + 1]);
		else if (data->child < 0)
			perror(FORK_ERR);
		else
			waitpid(data->child, &data->status, 0);
		i++;
	}
	ft_parent_cleanup(data);
}
