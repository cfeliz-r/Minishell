/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:54 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/11 13:29:29 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	manage_error(130, 0);
	rl_redisplay();
}

void	sigint_handler_here_doc(int sig)
{
	(void)sig;
	rl_on_new_line();
	ioctl(0, TIOCSTI, "\n");
	g_stop_status = 1;
}

void	sigint_handler_ha(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}
