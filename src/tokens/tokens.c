/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:39:10 by fracurul          #+#    #+#             */
/*   Updated: 2024/10/20 17:45:02 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_del(char c, const char *delimiter)
{
	int i;

	i = 0;
	while(delimiter[i])
	{
		if(delimiter[i] == c)
			return(TRUE);
		i++;
	}
	return(FALSE);
}

int is_ddel(char *input, const char delimiter, int i)
{
	if (!input[i] && !input[i + 1])
		return (FALSE);
	if(input[i] == delimiter && input[i + 1] == delimiter )
		return(TRUE);
	return(FALSE);
}

/*char *ft_strtok(char *line, const char *delimiter)
{
	static char *input = NULL; //guardar token entre llamadas.
	char *token;
	int i;
	int start;

	start = 0;
	if(line != NULL) //inicializamos input con el contenido de line.
		input = line;
	if(!input) //si no existe salimos.
		return(NULL);
	while(input[start] && is_del(*input, delimiter))//saltar del iniciales en caso de que haya.
		start++;
	if(input[start] == '\0')//si hemos llegado al final no existe token, por lo tanto salimos.
	{
		input = NULL;
		return(FALSE);
	}
	i = start;
	while(input[i])//recorremos la cadena
	{
		if(!is_in_quotes(input, i) && is_del(input[i], delimiter) //si hay un del, fuera de comilla, terminamos y avanzamos
			&&	!is_ddel(input, '>', i) && !is_ddel(input, '<', i))		
		{
			input[i] = '\0';
			token = &input[start];
			input = &input[i + 1];
			return (token);
		}
		if(!is_in_quotes(input, i) && (is_ddel(input, '>', i) //nuevo
			|| is_ddel(input, '<', i)))
		{
			input[i + 1] = '\0';
			token = &input[start + 1];
			input = &input[i + 2];
			return (token);//nuevo hasta aqui.
		}
		i++;
	}
	token = &input[start]; //si llegamos al final sin encontrar del
	input = NULL;
	return (token);
}

int count_words(char *str)
{
	int i;
	int wc;

	i = 0;
	wc = 0;
	while(str[i])
	{
		while(str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '|'))
			i++;
		if(str[i])
			wc++;
		while(str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '|'))
			i++;
	}
	return(wc);
}

char **tokenize_command(char *input, int pos)
{
	char **tokens; //doble array con los tokens
	char *token; //token simple
	const char *del = " \t|><"; //delimitadores
	int			count;

	tokens = (char **)malloc(count_words(input) * sizeof(char *));
	count = count_words(input);
	token = ft_strtok(input, del);
	while(token != NULL)
	{
		tokens[pos] = token;
		pos++;
		if(pos > count)
		{
			ft_putstr_fd("minishell: too much argumentens", 1);
			break;
		}
		token = ft_strtok(NULL, del);
	}
	tokens[pos] = NULL;
	return(tokens);
}*/

int count_words(char *str) {
    int wc = 0;
    int in_word = 0;

    while (*str) {
        if (is_del(*str, " \t")) {
            if (in_word) {
                in_word = 0;
            }
        } else {
            if (!in_word) {
                in_word = 1;
                wc++;
            }
        }
        str++;
    }
    return wc;
}

char *ft_strtok(char *line, const char *delimiter) {
    static char *input = NULL;
    char *token;
    int start;

    if (line != NULL)
        input = line;
    if (!input)
        return NULL;

    // Saltar los delimitadores iniciales
    while (*input && is_del(*input, delimiter))
        input++;

    if (*input == '\0') {
        input = NULL;
        return NULL;
    }

    token = input;  // El token empieza aquí
    start = 0;

    // Recorremos hasta encontrar un delimitador
    while (input[start]) {
        if (is_del(input[start], delimiter)) {
            // Si encontramos un delimitador, lo separamos
            if (start == 0) {
                input += 1;  // Avanzamos el input
                return strndup(token, 1);  // Devolvemos el delimitador como token
            }
            input[start] = '\0';  // Terminamos el token actual
            input += start + 1;   // Avanzamos para el siguiente token
            return token;
        }
        start++;
    }

    // Si no hay más delimitadores, retornamos el resto como un token
    input = NULL;
    return token;
}

t_token *tokenize_command(char *input, int *num_commands) {
    t_token *cmd = malloc(10 * sizeof(t_token));  // Máximo de 10 comandos (se puede ajustar)
    char *token;
    const char *del = " \t";  // Delimitadores
    int pos = 0;
    int parg = 0;

    *num_commands = 0;  // Inicializamos el número de comandos

    // Tokenizamos el primer comando
    token = ft_strtok(input, del);
    while (token != NULL) {
        if (is_del(*token, "| >>")) {  // Si encontramos un pipe, separamos el comando
            pos++;  // Avanzamos al siguiente comando
            parg = 0;  // Reiniciamos el contador de argumentos
            token = ft_strtok(NULL, del);  // Ignoramos el pipe
            continue;
        }

        // Guardamos el comando y sus argumentos
        if (parg == 0) {
            cmd[pos].cmd = strdup(token);  // Guardamos el comando principal
            cmd[pos].cargs = malloc(10 * sizeof(char*));  // Reservamos espacio para los argumentos
        } else {
            cmd[pos].cargs[parg - 1] = strdup(token);  // Guardamos el argumento
        }

        parg++;
        token = ft_strtok(NULL, del);  // Siguiente token
    }

    cmd[pos].cargs[parg - 1] = NULL;  // Terminamos la lista de argumentos
    *num_commands = pos + 1;  // Actualizamos el número de comandos
    return cmd;
}
