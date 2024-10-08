/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:47:00 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/08 15:19:51 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// States
# define TRUE 1
# define FALSE 0

// Errors
# define ARG_ERR "Error on the arguments"
# define PARS_ERR "Parsing error"
# define CD_ERR "Error on cd command"
# define PWD_ERR "Error on pwd command"
# define MALLOC_ERR "Malloc error"
# define SIGA_ERR "Sigaction error"
# define SIGEMPT_ERR "Sig empty set error"
# define SIGIGN_ERR "Failed to ignore SIGQUIT"
# define SETINT_ERR "Failed to set SIGINT handler"
# define SETINT_CHLD "Failed to set SIGINT handler for process"
# define SETIGN_CHLD "Failed to set SIGQUIT handler for process"

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