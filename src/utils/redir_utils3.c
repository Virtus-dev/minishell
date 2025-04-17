/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:23:37 by fracurul          #+#    #+#             */
/*   Updated: 2025/04/17 16:24:13 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirout(t_data *data, char *redir, int redir_type)
{
	int	new_fd;

	if (redir_type == S_OUT)
		new_fd = open(redir, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir_type == D_OUT)
	{
		new_fd = open (redir, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	if (new_fd == -1)
	{
		ft_putstr_fd(FILE_ERR, data->fdout);
		data->status = 1;
		return ;
	}
	data->fdout = new_fd;
}

void	ft_redirin(t_data *data, char *redir, int redir_type)
{
	int	new_fd;

	if (redir_type == S_IN)
		new_fd = open(redir, O_RDONLY);
	else if (redir_type == D_IN)
		ft_here_doc(data);
	if (new_fd == -1)
	{
		ft_putstr_fd(FILE_ERR, data->fdout);
		data->status = 1;
		return ;
	}
	data->fdin = new_fd;
}
