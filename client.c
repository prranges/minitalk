/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:54:38 by prranges          #+#    #+#             */
/*   Updated: 2021/09/02 15:54:41 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_bit(char c, int pid, char *message)
{
	static int	bit = -1;

	if (++bit < 8)
	{
		if (c & (0x80 >> bit))
		{
			if (kill(pid, SIGUSR1) == -1)
				error_quit(message, 'c');
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error_quit(message, 'c');
		}
	}
	if (bit == 7)
		bit = -1;
	return (0);
}

void	send_message(char *s, int pid)
{
	static int	bit = -1;
	static char	*message = 0;
	static int	saved_pid = 0;

	if (s)
		message = ft_strdup(s);
	if (pid)
		saved_pid = pid;
	send_bit(message[++bit / 8], saved_pid, message);
}

void	client_handler_SIGUSR(int sig)
{
	if (sig == SIGUSR1)
		send_message(0, 0);
	if (sig == SIGUSR2)
	{
		write(1, "server: Message recived!\n", 25);
		exit (0);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	signals;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	signals.sa_mask = block_mask;
	signals.sa_handler = &client_handler_SIGUSR;
	sigaction(SIGUSR1, &signals, NULL);
	sigaction(SIGUSR2, &signals, NULL);
	if (argc != 3 || check_pid(argv[1]))
	{
		ft_putstr_fd("client: Wrong arguments!\n", 2);
		ft_putstr_fd("\tCorrect format: ./client <PID> <MESSAGE>\n", 2);
		exit(EXIT_FAILURE);
	}
	send_message(argv[2], ft_atoi(argv[1]));
	while (1)
		pause();
}
