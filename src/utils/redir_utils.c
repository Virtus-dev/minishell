/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:03:48 by arigonza          #+#    #+#             */
/*   Updated: 2025/02/09 14:50:36 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_sout(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] != '>')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_is_dout(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_is_sin(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_is_din(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<<' && str[i + 1] == '<<')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_rediout_type(char * str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] != '>')
			return (S_OUT);
		else if (str[i] == '>' && str[i + 1] == '>')
			return (D_OUT);
		i++;
	}
}

int	ft_redin_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
			return (S_IN);
		else if (str[i] == '<<' && str[i + 1] == '<<')
			return (D_IN);
		i++;
	}
}

int	ft_redir_pos(char **argv)
{
	int	i;

	if (!argv)
		return (perror(ARG_ERR), FALSE);
	i = 0;
	while (argv[i])
	{
		if (ft_is_sout(argv[i]) || ft_is_dout(argv[i]) || 
			ft_is_sin(argv[i]) || ft_is_din(argv[i]))
			return (i);
		i++;
	}
	return (FALSE);
}

void	ft_redirout(t_data *data, char *redir, int redir_type)
{
	int	new_fd;
	
	if (redir_type == S_OUT)
    	new_fd = open(redir, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    else if (redir_type == D_OUT)
    	new_fd = open (redir, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (new_fd == -1)
	{
		ft_putstr_fd("Error opening file\n", data->fdout);
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
    else if (redir_type == D_OUT)
	// There i must implement a here_doc function
	if (new_fd == -1)
	{
		ft_putstr_fd("Error opening file\n", data->fdout);
		data->status = 1;
		return ;
	}
	data->fdin = new_fd;
}