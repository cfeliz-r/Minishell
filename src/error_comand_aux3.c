/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand_aux3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:24:25 by manufern          #+#    #+#             */
/*   Updated: 2024/08/20 15:26:09 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_quotes_3(char **start)
{
	char	quote_char;

	quote_char = **start;
	(*start)++;
	while (**start && **start != quote_char)
		(*start)++;
	if (**start != quote_char)
		return (0);
	(*start)++;
	return (1);
}
