/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:52:31 by edu               #+#    #+#             */
/*   Updated: 2022/11/10 12:30:21 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	better_kill(int pid, int signal)
{
	kill(pid, signal);
	usleep(100);
}

int	terminate_string(int pid)
{	
	static int	index = 0;

	if (index++ != 8)
	{
		kill(pid, SIGUSR1);
		return (0);
	}
	return (1);
}

int	send_message(char *str, int pid)
{
	static char	*msg = 0;
	static int	server_pid = 0;
	static int	index = -1;

	if (str)
		msg = ft_strdup(str);
	if (pid)
		server_pid = pid;
	if (msg[++index / 8])
	{
		if (msg[index / 8] & (128 >> (index % 8)))
			better_kill(server_pid, SIGUSR2);
		else
			better_kill(server_pid, SIGUSR1);
		return (0);
	}
	if (!terminate_string(server_pid))
		return (0);
	free(msg);
	return (1);
}

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	if (signal == SIGUSR1)
	{
		ft_printf("Received signal!\n");
		send_message(0, 0);
	}
	if (signal == SIGUSR2)
	{
		ft_printf("Success!\n");
		exit(0);
	}
	(void)info;
	(void)ucontext;
}

int	main(int argc, char *argv[])
{	
	struct sigaction	sigact;
	sigset_t			set;
	int					pid;

	if (argc != 3)
		return (ft_printf("Usage: ./client [PID] [STRING]\n"));
	pid = ft_atoi(argv[1]);
	sigemptyset(&set);
	sigact.sa_mask = set;
	sigact.sa_flags = 0;
	sigact.sa_sigaction = handler;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	send_message(argv[2], pid);
	while (1)
		pause();
	return (0);
}
