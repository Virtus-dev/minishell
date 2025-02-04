/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:13:55 by arigonza          #+#    #+#             */
/*   Updated: 2025/02/04 17:46:48 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_start_redi(t_data *data)
{
    int     new_fd;
    int     redir_pos;
    char    **split;
    

    split = ft_split(data->input, ' ');
    redir_pos = ft_redir(split);
    new_fd = open (split[redir_pos + 1], O_RDWR);
}