/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:43:55 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/23 17:20:50 by arigonza         ###   ########.fr       */
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
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_check_expformat(char *argv)
{
	int		i;

	i = 0;
	if (argv[0] != '_' || ft_isalpha(argv[0]))
		return (FALSE);
	i++;
	while (argv[i])
	{
		if (!ft_isalnum(argv[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}