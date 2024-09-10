/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:31 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/09 15:38:29 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include "constants.h"
#include <sys/types.h>
#include <sys/errno.h>
#include <signal.h>

// Structs
typedef struct	s_token
{
    char	*str;
    int		type;
    int		space;
    struct s_token	*prev;
    struct s_token	*next;
}	t_token;

typedef struct	s_data
{
    char        *input;
    char        **argv;
    t_token		*token;
    int         argc;
    pid_t       child;
    int         fdin;
    int         fdout;
} t_data;

void    ft_echo(char *msg);


#endif
