/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/08/23 12:17:06 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

int main()
{
	char	*input;

	printf("ctrl+D para salir\n");
	while (input = readline("Write something") != NULL)
	{
		if (input && *input)
		{
			add_history(input);
		}
		else
		{
		free(input);
		break;
		}
	}
	free(input);
	clear_history();
	return (0);
}
