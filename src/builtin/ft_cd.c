/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:54:35 by manufern          #+#    #+#             */
/*   Updated: 2024/08/21 11:48:29 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Función para eliminar comillas al principio y al final de una cadena
static char *remove_quotes(char *str)
{
    char *cleaned_str;
    size_t len;

    if (str == NULL)
        return (NULL);
    
    len = ft_strlen(str);
    
    // Verificar si la cadena comienza y termina con comillas
    if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))
    {
        // Crear nueva cadena sin comillas
        cleaned_str = malloc(len - 1);
        if (cleaned_str == NULL)
            return (NULL);
        memcpy(cleaned_str, str + 1, len - 2);
        cleaned_str[len - 2] = '\0';
        return (cleaned_str);
    }
    
    // Si no hay comillas, retornar la cadena original
    return (str);
}

void ft_cd(char *route)
{
    char **str_route;
    int i;

    i = 0;
    str_route = ft_split(route, ' ');

    // Verificar y eliminar comillas de la ruta si es necesario
    if (str_route[1] != NULL)
    {
        char *cleaned_route = remove_quotes(str_route[1]);
        if (cleaned_route != NULL)
        {
            // Verificar la validez de la ruta y cambiar directorio
            if (i > 2)
                printf("cd: string not in pwd: %s\n", str_route[1]);
            else
            {
                if (access(cleaned_route, F_OK | R_OK) == 0)
                    chdir(cleaned_route);
                else
                {
                    perror("cd");
                    manage_error(1, 0);
                }
            }
            
            if (cleaned_route != str_route[1])
                free(cleaned_route);
        }
        else
        {
            printf("cd: memory allocation error\n");
            manage_error(1, 0);
        }
    }

    // Liberar memoria de los argumentos divididos
    clean_up(str_route, NULL, 0);
}
