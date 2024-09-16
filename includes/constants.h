/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:47:00 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/16 16:51:15 by arigonza         ###   ########.fr       */
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

// Constants
# define PATH_MAX 5

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