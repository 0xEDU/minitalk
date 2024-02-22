/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:52:31 by edu               #+#    #+#             */
/*   Updated: 2024/02/21 23:09:16 by etachott         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_message(int server_pid, char *str)
{
	static int	index = 0;
	static int	msg_bit_pos = -1;
	static char	*msg = NULL;

	if (str)
	{
		msg = str;
		msg[ft_strlen(str) + 1] = '\0';
	}
	if (msg[++msg_bit_pos / 8])
	{
		if (msg[msg_bit_pos / 8] & (128 >> (msg_bit_pos % 8)))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		return (0);
	}
	if (index++ != 8)
	{
		kill(server_pid, SIGUSR1);
		return (0);
	}
	msg = NULL;
	return (1);
}

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	if (signal == SIGUSR1 && send_message(info->si_pid, NULL) != 0)
		exit(ft_printf("Success!\n"));
	(void)ucontext;
}

int	main(int argc, char *argv[])
{
	struct sigaction	sigact;
	sigset_t			set;

	if (argc != 3)
		return (ft_printf("Usage: ./client [PID] [STRING]\n"));
	sigemptyset(&set);
	sigact.sa_mask = set;
	sigact.sa_flags = 0;
	sigact.sa_sigaction = handler;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	send_message(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
