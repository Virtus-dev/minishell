/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:50:15 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/21 19:21:40 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strchr_mn(char *str, int c)
{
	if (!str)
		return (FALSE);
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int	ft_is_expandable(char *var)
{
	if (var[0] != '\'' && ft_strchr_mn(var, '$'))
		return (TRUE);
	else
		return (FALSE);
}
