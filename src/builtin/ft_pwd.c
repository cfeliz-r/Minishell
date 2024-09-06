/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:55 by manufern          #+#    #+#             */
/*   Updated: 2024/09/06 19:57:53 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_list_env **envp)
{
    static char	buf[PATH_MAX];

    if (getcwd(buf, PATH_MAX) == NULL)
    {
        while (*envp)
        {
            if (compare_until_equal_sign((*envp)->envp_content, "ROUTE") == 1) // Usar 'envp_content' en lugar de 'content'
            {
                printf("%s\n", (*envp)->envp_content + 6);  // Usar 'envp_content' en lugar de 'content'
                break ;
            }
            *envp = (*envp)->next;
        }
        return ;
    }
    printf("%s\n", buf);
    manage_error(0, 0);
}
