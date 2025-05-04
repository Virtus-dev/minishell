/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:10:26 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/02 12:45:20 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_token_result(t_token **cmds)
{
    int    i;
    int    j;

    if (!cmds)
        return;
    i = 0;
    while (cmds[i])
    {
        if (cmds[i]->cmd)
            free(cmds[i]->cmd);
        if (cmds[i]->cargs)
        {
            j = 0;
            while (cmds[i]->cargs[j])
                free(cmds[i]->cargs[j++]);
            free(cmds[i]->cargs);
        }
        free(cmds[i]);
        i++;
    }
    free(cmds);
}

void    print_cmd_structure(t_token **cmds)
{
    int    i = 0;
    int    j;

    while (cmds[i])
    {
        printf("  ➤ Comando[%d]: %s\n", i, cmds[i]->cmd ? cmds[i]->cmd : "(null)");
        j = 0;
        while (cmds[i]->cargs && cmds[i]->cargs[j])
        {
            printf("Arg[%d]: %s\n", j, cmds[i]->cargs[j]);
            j++;
        }
        i++;
    }
}

void    run_tokenizer_test(const char *input)
{
    char        **tokens;
    t_token     **cmds;

    printf("🟡 Input: %s\n\n", input);
    tokens = tokenizer(input);

    printf("Tokens generados por tokenizer():\n");
    for (int i = 0; tokens[i]; i++)
        printf("  [%d]: %s\n", i, tokens[i]);
    printf("\n");

    cmds = tokenize_command(tokens);
    print_cmd_structure(cmds);

    printf("✅ Comandos correctamente agrupados (bash-like)\n");
    printf("--------------------------------------------------\n");

    ft_free_matrix(tokens);
    free_token_result(cmds);
}

int    main(void)
{
    // 🔁 Esto reemplaza el bucle infinito mientras probás con Valgrind
    run_tokenizer_test("echo \"hola mundo\" | wc -l");
    run_tokenizer_test("cat <<EOF | grep error > salida.txt");
    run_tokenizer_test("ls -la | grep main.c | wc -l");
    run_tokenizer_test("ls -la | \"grep main.c\"");
    run_tokenizer_test("echo 'esto > no es redir'");
    run_tokenizer_test("cat < entrada.txt >> salida.txt");
    run_tokenizer_test("echo '' | grep hola > file.txt");
    run_tokenizer_test("grep | \"archivo.txt\"");
    run_tokenizer_test("ls | cat -e | tr -d '\n'");
    run_tokenizer_test("cd -\n");
    run_tokenizer_test("cat");

    return (0);
}