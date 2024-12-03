/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/12/03 16:18:11 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


/*int main(int argc, char **argv, char **env)
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
        //printf("Entrada: %s\n", input);
        data->tokens = tokenize_command(input);
        ft_load_args(data, data->tokens[0]);
        //printf("data->argv[0] = %s\n", data->argv[0]);
        if (ft_builtin_check(data->argv[0]))
        {
            printf("On exec_builtin\n");
            ft_exec_built(data, data->argv[0]);
        }
        else
        {
            printf("On ft_exec\n");
            ft_exec(data);
        }
        // If we have input, add it to the history
        if (input && *input)
        {
            add_history(input);
        }

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
}*/

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
        if(ft_strlen(input) == 0)// hay que arreglar esta linea ctrl + D no funciona correctamente
        {
            free(input);
            continue;
        }
        // If no input (Ctrl+D), exit the shell
        if(!check_input(input))
        {
            free(input);
            printf("Closing minishell...\n");
            break;
        }
        //printf("Entrada: %s\n", input);
        data->tokens = tokenize_command(input);
        ft_load_args(data, data->tokens[0]);
        //printf("data->argv[0] = %s\n", data->argv[0]);
        if (ft_builtin_check(data->argv[0]))
        {
            printf("On exec_builtin\n");
            ft_exec_built(data, data->argv[0]);
        }
        else
        {
            printf("On ft_exec\n");
            ft_exec(data);
        }
        // If we have input, add it to the history
        if (input && *input)
        {
            add_history(input);
        }

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