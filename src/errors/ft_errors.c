/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:40:53 by manufern          #+#    #+#             */
/*   Updated: 2024/08/05 17:41:58 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Función que maneja códigos de error y números
int manage_error(int error_code, int return_value)
{
    static int error_var = 0; // Variable estática para almacenar el código de error

    if (return_value == 0)
    {
        // Actualiza la variable estática con el código de error
        error_var = error_code;
        return -1; // Indicamos que no se está devolviendo el valor de error_var
    } else if (return_value == 1)
    {
        // Devuelve el valor de la variable estática
        return error_var;
    }
    return -1; // Código de error por defecto
}