/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:40:53 by manufern          #+#    #+#             */
/*   Updated: 2024/09/09 16:50:38 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int manage_error(int error_code, int return_value)
{
    static int error_var = 0;

    if (return_value == 0)
    {
        error_var = error_code;
        return (-1);
    }
    else if (return_value == 1)
    {
        return (error_var);
    }
    return (-1);
}
