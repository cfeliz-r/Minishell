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
    char *buf;
    size_t size = 1024;

    buf = malloc(size * sizeof(char));
    if (buf == NULL)
	{
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (getcwd(buf, size) == NULL)
	{
        perror("getcwd");
        free(buf);
        exit(EXIT_FAILURE);
    }

    printf("%s\n", buf);
    free(buf);
}