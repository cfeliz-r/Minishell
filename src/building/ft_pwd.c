 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:55 by manufern          #+#    #+#             */
/*   Updated: 2024/07/24 09:45:31 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_pwd(void)
{
    static char buf[1024 + 1];

    if (buf == NULL)
        perror("malloc");
    if (getcwd(buf, 1024 + 1) == NULL)
        return ;
    if (buf != NULL)
        printf("%s\n", buf);
    else
        printf("%s\n", buf);
}