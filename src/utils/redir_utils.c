/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:03:48 by arigonza          #+#    #+#             */
/*   Updated: 2025/02/04 17:43:38 by arigonza         ###   ########.fr       */
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
		if (str[i] == '<' && str[i + 1] == '<')
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
int	ft_redin_type(char * str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
			return (S_IN);
		else if (str[i] == '<' && str[i + 1] == '<')
			return (D_IN);
		i++;
	}
}

int	ft_redir(char **argv)
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