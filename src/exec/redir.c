/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:13:55 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/21 18:28:51 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_redi(t_data *data, t_token *token)
{
	int		j;
	int		type;

	printf("EN START REDIRECTIONS!!\n");
	j = 0;
	while (token->cargs && token->cargs[j])
	{
		type = ft_redir_type(token->cargs[j]);
		if (type == S_OUT || type == D_OUT)
		{
			if (token->cargs[j + 1])
			{
				ft_redirout(data, token->cargs[j + 1], type);
				j++;
			}
		}
		else if (type == S_IN || type == D_IN)
		{
			if (token->cargs[j + 1])
			{
				ft_redirin(data, token->cargs[j + 1], type);
				j++;
			}
		}
		j++;
	}
}

int	ft_redir_type(const char *arg)
{
	if (!arg)
		return (-1);
	if (ft_strcmp(arg, ">") == 0)
		return (S_OUT);
	if (ft_strcmp(arg, ">>") == 0)
		return (D_OUT);
	if (ft_strcmp(arg, "<") == 0)
		return (S_IN);
	if (ft_strcmp(arg, "<<") == 0)
		return (D_IN);
	return (-1);
}

void	ft_redirout(t_data *data, char *file, int type)
{
	int	fd;

	if (type == S_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		perror("redirout");
		data->status = 1;
		return ;
	}
	if (data->fdout != STDOUT_FILENO)
		close(data->fdout);
	data->fdout = fd;
}

void	ft_redirin(t_data *data, char *file, int type)
{
	int	fd;

	if (type == S_IN)
		fd = open(file, O_RDONLY);
	else
	{
		ft_here_doc(data, file);
		return ;
	}
	if (fd < 0)
	{
		perror("redirin");
		data->status = 1;
		return ;
	}
	if (data->fdin != STDIN_FILENO)
		close(data->fdin);
	data->fdin = fd;
}
