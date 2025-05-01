/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:03:48 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/01 12:43:52 by arigonza         ###   ########.fr       */
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
		printf("str[%d] = %c\n", i, str[i]);
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
