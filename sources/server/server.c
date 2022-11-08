/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:51:33 by edu               #+#    #+#             */
/*   Updated: 2022/11/08 08:25:30 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	char_maker(t_byte *byte)
{
	unsigned char	c;
	int 			i;

	i = 0;
	c = 0;
	while (i < 8)
	{
		c = c << 1;
		c = c | byte[i].bit;
		i++;
	}
	return (c);
}

void	init_msg(t_msg *msg)
{
	msg->init = 1;
	msg->byte = malloc(sizeof(t_byte) * 8);
	msg->index = 0;
}

void	reset_msg(t_msg *msg)
{
	msg->init = 0;
	free(msg->byte);
	msg->index = 0;
}

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	static t_msg	msg;
	char			c;

	(void)ucontext;
	(void)info;
	c = 0;
	if (!msg.init)
		init_msg(&msg);
	if (signal == SIGUSR1)
		msg.byte[msg.index].bit = 0;
	if (signal == SIGUSR2)
		msg.byte[msg.index].bit = 1;
	if (msg.index == 7)
	{
		c = char_maker(msg.byte);
		write(1, &c, 1);
		write(1, "\0", 1);
		reset_msg(&msg);
	}
	msg.index++;
	usleep(300);
}

void	teste(int signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	ft_printf("SIGNAL %d RECEIVED\n", signal);
}

int	main(void)
{
	struct sigaction	sigact;
	sigset_t			set;
	

	sigemptyset(&set);
	sigact.sa_mask = set;
	sigact.sa_flags = 0;
	sigact.sa_sigaction = handler;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
