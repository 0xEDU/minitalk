/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:51:33 by edu               #+#    #+#             */
/*   Updated: 2024/02/21 21:46:48 by etachott         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	static char		c = 0xFF;
	static int		index = 0;
	const int		pid = info->si_pid;

	if (signal == SIGUSR1)
		c ^= 0x80 >> index++;
	if (signal == SIGUSR2)
		c |= 0x80 >> index++;
	if (index == 8)
	{
		if (c == '\0')
			ft_printf("\n");
		write(1, &c, 1);
		c = 0xFF;
		index = 0;
	}
	kill(pid, SIGUSR1);
	(void)ucontext;
}

int	main(void)
{
	struct sigaction	sigact;
	sigset_t			sigset;

	sigemptyset(&sigset);
	sigact.sa_mask = sigset;
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = handler;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
