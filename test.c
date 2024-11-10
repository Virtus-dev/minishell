/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/11/10 15:27:21 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


int main(int argc, char **argv, char **env)
{
    (void)argv;
    t_data  *data;
    char    *input;

    data = ft_init_data(argc, env);

    while (1)
    {
        // Read user input
        input = readline("Minishell$ ");
        
        // If no input (Ctrl+D), exit the shell
        if (!input)
        {
            printf("Exit\n");
            perror("NO input");
        }
        printf("Entrada: %s\n", input);
        data->tokens = tokenize_command(input);
        ft_load_args(data);
        // Print the input for testing purposes
        //printf("data arguments[0] = %s\n",data->tokens[2].cmd);
        ft_exec(data);
        // If we have input, add it to the history
        if (input && *input)
        {
            add_history(input);
        }

        ft_free_matrix(data->argv);
        // Free the input to avoid memory leaks
        free(input);
        //ft_free_matrix(data->argv);
    }

    // Free allocated data before exiting
    ft_free_resources(data);

    return 0;
}

void free_tokens(t_token **tokens) {
    int i = 0;
    while (tokens[i]) {
        free(tokens[i]->cmd);
        ft_free_matrix(tokens[i]->cargs);
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

/*
int main() {
    char str[100] = "echo -n 'hola' >> test.txt";
    int num_commands = 0;
    t_token *commands = tokenize_command(str, &num_commands);
    int i = 0;
    int j = 0;

    // Imprimimos los resultados
    while (commands[i].cmd) {
        printf("Command: %s\n", commands[i].cmd);
        printf("Arguments: ");
        while (commands[i].cargs[j] && j < 2) {
            printf("%s ", commands[i].cargs[j]);
            j++;
        }
        i++;
        printf("\n");
    }

    // Liberamos la memoria
    free_tokens(commands, num_commands);

    return 0;
}
*/