/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:56:19 by fracurul          #+#    #+#             */
/*   Updated: 2025/05/12 11:56:59 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_flag(char **av, int *nl)
{
	int	i;
	int	j;

	*nl = 0;
	i = 1;
	while (av[i])
	{
		if (av[i][0] != '-' || av[i][1] != 'n')
			break ;
		j = 2;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] != '\0')
			break ;
		i++;
	}
	if (i > 1 && av[i] && av[i][0] == '-' && av[i][1] != 'n')
		*nl = 0;
	else if (i > 1)
		*nl = 1;
	return (i);
}
