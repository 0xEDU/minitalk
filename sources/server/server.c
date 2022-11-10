/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:51:33 by edu               #+#    #+#             */
/*   Updated: 2022/11/10 12:44:44 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	char_maker(t_byte *byte)
{
	unsigned char	c;
	int				i;

	i = 0;
	c = 0;
	while (i < 8)
	{
		c <<= 1;
		c |= byte[i].bit;
		i++;
	}
	return (c);
}

void	msg_setter(t_msg *msg, char flag)
{
	if (flag == 'i')
	{
		msg->init = 1;
		msg->index = 0;
		msg->byte = ft_calloc(sizeof(t_byte), 8);
	}
	else if (flag == 'r')
	{
		msg->init = 0;
		msg->index = 0;
		free(msg->byte);
	}
}

void	end_byte(t_msg *msg, char c, int pid)
{
	c = char_maker(msg->byte);
	if (c == '\0')
	{
		kill(pid, SIGUSR2);
		ft_printf("\n");
	}
	write(1, &c, 1);
	msg_setter(msg, 'r');
}

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	static t_msg	msg;
	int				pid;
	char			c;

	c = 0;
	pid = info->si_pid;
	if (!msg.init)
		msg_setter(&msg, 'i');
	if (signal == SIGUSR1)
	{
		msg.byte[msg.index].bit = 0;
		kill(pid, SIGUSR1);
	}
	if (signal == SIGUSR2)
	{
		msg.byte[msg.index].bit = 1;
		kill(pid, SIGUSR1);
	}
	if (msg.index == 7)
		end_byte(&msg, c, pid);
	msg.index++;
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
