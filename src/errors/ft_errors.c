/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:40:53 by manufern          #+#    #+#             */
/*   Updated: 2024/09/12 11:01:36 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	manage_error(int error_code, int return_value)
{
	static int	error_var = 0;

	if (return_value == 0)
	{
		error_var = error_code;
		return (-1);
	}
	else if (return_value == 1)
		return (error_var);
	return (-1);
}
