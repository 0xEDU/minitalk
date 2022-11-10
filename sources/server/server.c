/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:51:33 by edu               #+#    #+#             */
/*   Updated: 2022/11/10 10:14:48 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	byte_printer(t_byte *byte)
{
	printf("\nBYTE!");
	printf("\n[%d, %d, %d, %d, %d, %d, %d, %d]\n", byte[0].bit, byte[1].bit, byte[2].bit, byte[3].bit, byte[4].bit, byte[5].bit, byte[6].bit, byte[7].bit);
}

unsigned char	char_maker(t_byte *byte)
{
	unsigned char	c;
	int 			i;

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

void	init_msg(t_msg *msg)
{
	msg->init = 1;
	msg->index = 0;
	msg->byte = ft_calloc(sizeof(t_byte), 8);
}

void	reset_msg(t_msg *msg)
{
	msg->init = 0;
	msg->index = 0;
	free(msg->byte);
}

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	static t_msg	msg;
	int		pid = 0;
	char			c;

	c = 0;
	pid = info->si_pid;
	if (!msg.init)
		init_msg(&msg);
	if (signal == SIGUSR1)
		msg.byte[msg.index].bit = 0;
	if (signal == SIGUSR2)
		msg.byte[msg.index].bit = 1;
	if (msg.index == 7)
	{
		//byte_printer(msg.byte);
		c = char_maker(msg.byte);
		if (c == '\0')
		{
			kill(pid, SIGUSR2);
			ft_printf("\n");
		}
		write(1, &c, 1);
		reset_msg(&msg);
		usleep(8000);
		kill(pid, SIGUSR1);
	}
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
