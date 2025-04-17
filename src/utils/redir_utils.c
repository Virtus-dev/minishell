/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:03:48 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 16:23:56 by fracurul         ###   ########.fr       */
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

int	ft_rediout_type(char *str)
{
	if (ft_is_sout(str))
		return (S_OUT);
	else if (ft_is_dout(str))
		return (D_OUT);
	return (0);
}

//apartir de aqui
