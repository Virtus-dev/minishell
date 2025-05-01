/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:43:55 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/01 09:50:05 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Looks for a flag on the echo command.
 *
 * @param str
 * @return int return 1, in case there's a flag, 0 en case it's not.
 */
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

/**
 * @brief Checks if the path for de export have the right format.
 *
 * @param argv
 * @return int
 */
int	ft_check_expformat(char *argv)
{
	int		i;

	i = 0;
	if (argv[0] != '_' && ft_isdigit(argv[0]))
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

/**
 * @brief Free a char doble pointer (char**).
 *
 * @param matrix The char double pointer to be freed.
 */
void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

/**
 * @brief Clean up all the resources on the t_data structure.
 *
 * @param data
 */
void	ft_free_resources(t_data *data)
{
	if (!data)
		return ;
	if (data->argv)
	{
		ft_free_matrix(data->argv);
		data->argv = NULL;
	}
	if (data->tokens)
		free_tokens(data->tokens);
	ft_free_map(data->env);
	ft_free_map(data->exp);
}
