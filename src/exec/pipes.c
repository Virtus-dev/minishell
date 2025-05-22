/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:14:16 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/22 19:58:51 by fracurul         ###   ########.fr       */
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
			return (1);
		j++;
	}
	return (0);
}

void	ft_swapfd(t_data *data, int i, int pipe_num)
{
	int		fd[2];
	t_token	*token;

	if (pipe(fd) == -1)
	{
		perror(PIPE_ERR);
		return ;
	}
	token = data->tokens[i];
	if (i == pipe_num)
		data->fdout = STDOUT_FILENO;
	else
		data->fdout = fd[1];
	if (token && has_redirection(token))
		ft_start_redi(data, token);
	close(fd[1]);
	if (i == 0)
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

/*void	ft_pipe_processing(t_data *data, int pipe_num)
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
		//printf("comando a ejecutar: %s\n", data->argv[0]);
		//printf("comando a ejecutar: %d\n", curr_token->cmd[0]);
		if (ft_nonenv_builtin(curr_token->cmd)
			|| (ft_is_env_builtin(curr_token->cmd) && !next_token))
			ft_exec_built(data, curr_token->cmd);
		else
			ft_exec(data);
		i++;
	}
	ft_close_fds(data);
}*/
//PRUEBA
static void	ft_dup_io(t_data *data)
{
	if (data->fdin != STDIN_FILENO)
	{
		dup2(data->fdin, STDIN_FILENO);
		close(data->fdin);
	}
	if (data->fdout != STDOUT_FILENO)
	{
		dup2(data->fdout, STDOUT_FILENO);
		close(data->fdout);
	}
}

static void	ft_execute_pipe_cmd(t_data *data, t_token *curr, t_token *next)
{
	pid_t	pid;

	(void)next;
	pid = fork();
	if (pid == 0)
	{
		ft_dup_io(data);
		if (ft_builtin_check(curr->cmd))
			ft_exec_built(data, curr->cmd);
		else
			ft_exec(data);
		exit(data->status);
	}
	else
		waitpid(pid, &data->status, 0);
}

static void	ft_perror_and_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	ft_pipe_processing(t_data *data, int pipe_num)
{
	int		i;
	t_token	*curr;
	t_token	*next;

	i = 0;
	while (i <= pipe_num)
	{
		curr = data->tokens[i];
		next = data->tokens[i + 1];
		if (!curr || !curr->cmd)
			return (ft_perror_and_exit("Command not found"));

		ft_load_args(data, curr);
		ft_clean_and_replace_args(data);
		ft_swapfd(data, i, pipe_num);
		ft_execute_pipe_cmd(data, curr, next);
		i++;
	}
	ft_close_fds(data);
}
