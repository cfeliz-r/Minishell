/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:46:24 by manufern          #+#    #+#             */
/*   Updated: 2024/08/05 18:27:02 by manufern         ###   ########.fr       */
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
        manage_error(200, 0);
        return;
    }
    while (aux != NULL)
	{
        printf("%s\n", aux->envp_content);
        aux=aux->next;
    }
    manage_error(0, 0);
}
