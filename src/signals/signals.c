/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:54 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/20 15:49:34 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	sigint_handler_2(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_ha(int sig)
{
	(void)sig;
	exit(0);
}
