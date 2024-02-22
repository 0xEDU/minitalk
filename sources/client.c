/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:52:31 by edu               #+#    #+#             */
/*   Updated: 2024/02/21 22:43:15 by etachott         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_message(char *str, int server_pid)
{
	static int	index = 0;
	static int	msg_bit_pos = -1;
	static char	*msg = 0;

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
	if (signal == SIGUSR1)
	{
		if (send_message(0, info->si_pid))
		{
			ft_printf("Success!\n");
			exit(0);
		}
	}
	(void)ucontext;
}

int	main(int argc, char *argv[])
{	
	struct sigaction	sigact;
	sigset_t			set;
	int					server_pid;

	if (argc != 3)
		return (ft_printf("Usage: ./client [PID] [STRING]\n"));
	server_pid = ft_atoi(argv[1]);
	sigemptyset(&set);
	sigact.sa_mask = set;
	sigact.sa_flags = 0;
	sigact.sa_sigaction = handler;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	send_message(argv[2], server_pid);
	while (1)
		pause();
	return (0);
}
