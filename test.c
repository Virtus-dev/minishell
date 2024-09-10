/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/11 00:00:10 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main()
{
	char	*input;

	printf("Press ctrl+D to exit\n");
	while ((input = readline(NULL)) != NULL)
	{
		if (input && *input)
		{
			add_history(input);
		}
		if (!ft_strcmp(input, "pwd"))
			ft_pwd();
	}
	free(input);
	clear_history();
	return (0);
}
