/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:47:00 by arigonza          #+#    #+#             */
/*   Updated: 2025/03/13 12:00:35 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// States
# define TRUE 1
# define FALSE 0

// Errors
# define ARG_ERR "Error on the arguments\n"
# define PARS_ERR "Parsing error\n"
# define CD_ERR "Error on cd command\n"
# define PWD_ERR "Error on pwd command\n"
# define MALLOC_ERR "Malloc error\n"
# define SIGA_ERR "Sigaction error\n"
# define SIGEMPT_ERR "Sig empty set error\n"
# define SIGIGN_ERR "Failed to ignore SIGQUIT\n"
# define SETINT_ERR "Failed to set SIGINT handler\n"
# define SETINT_CHLD "Failed to set SIGINT handler for process\n"
# define SETIGN_CHLD "Failed to set SIGQUIT handler for process\n"
# define TOK_ERR "Token NULL\n"
# define PIPE_ERR "Pipe error\n"
# define FORK_ERR "Fork error\n"
# define BAD_INPUT "Bad input or NULL\n"
# define FILE_ERR "Error opening file\n"

// Constants
# define PATH_MAX 5
# define ECHO 1
# define CD 2
# define PWD 3
# define EXP 4
# define UNST 5
# define ENV 6
# define EXIT 7
# define DEF 8
# define S_OUT 10
# define D_OUT 11
# define S_IN 12
# define D_IN 13

// Colors Start
# define FRED "\033[0;31m"
# define FGREEN "\033[0;32m"
# define FYELLOW "\033[0;33m"
# define FBLUE "\033[0;34m"
# define FPURPLE "\033[0;35m"
# define WHITE "\033[0;37m"
# define DEF_COLOR "\033[0;39m"
// Colors End

#endif