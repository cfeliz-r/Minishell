/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:46:24 by manufern          #+#    #+#             */
/*   Updated: 2024/08/04 10:00:06 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(t_list_env *env)
{
    t_list_env *aux;

    aux = env;
    if (env == NULL)
	{
        printf("las nuestras\n");
        return;
    }
    while (aux != NULL)
	{
        printf("%s\n", aux->envp_content);
        aux=aux->next;
    }
}
