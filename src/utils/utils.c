/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:43:55 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/19 12:14:58 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_flag_exist(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '-')
	{
		if (str[i] == 'n')
			return (1);
		i++;
	}
	return (0);
}

