/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:54:55 by prranges          #+#    #+#             */
/*   Updated: 2021/09/02 15:55:03 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*print_message(char **message, int client_pid)
{
	ft_putstr_fd(*message, 1);
	if (kill(client_pid, SIGUSR2) == -1)
		error_quit(*message, 's');
	return (NULL);
}

void	server_handler_SIGUSR(int sig, siginfo_t *siginfo, void *context)
{
	static char		a = 0xFF;
	static int		bit = 0;
	static char		*message = 0;
	static int		client_pid = 0;

	(void)context;
	if (siginfo->si_pid)
		client_pid = siginfo->si_pid;
	if (sig == SIGUSR2)
		a ^= 0x80 >> bit;
	else if (sig == SIGUSR1)
		a |= 0x80 >> bit;
	if (++bit == 8)
	{
		if (a)
			message = str_add_char(message, a);
		else
			message = print_message(&message, client_pid);
		bit = 0;
		a = 0xFF;
	}
	if (kill(client_pid, SIGUSR1) == -1)
		error_quit(message, 's');
}

int	main(void)
{
	struct sigaction	signals;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	signals.sa_handler = 0;
	signals.sa_flags = SA_SIGINFO;
	signals.sa_mask = block_mask;
	signals.sa_sigaction = &server_handler_SIGUSR;
	sigaction(SIGUSR1, &signals, NULL);
	sigaction(SIGUSR2, &signals, NULL);
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
}
