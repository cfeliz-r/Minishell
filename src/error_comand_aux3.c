/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand_aux3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:24:25 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 17:53:46 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_quotes_3(char **start)
{
	char	quote_char;

	quote_char = **start;
	(*start)++;
	while (**start != '\0' && **start != quote_char)
		(*start)++;
	if (**start != quote_char)
		return (0);
	(*start)++;
	return (1);
}
