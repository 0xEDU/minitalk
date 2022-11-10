/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:52:31 by edu               #+#    #+#             */
/*   Updated: 2022/11/10 12:25:20 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	byte_printer(t_byte *byte)
{
	printf("\nBYTE!");
	printf("\n[%d, %d, %d, %d, %d, %d, %d, %d]\n", byte[0].bit, byte[1].bit, byte[2].bit, byte[3].bit, byte[4].bit, byte[5].bit, byte[6].bit, byte[7].bit);
}

t_byte	*byte_maker(unsigned char c)
{
	t_byte	*byte;
	int		i;

	i = 7;
	byte = malloc(sizeof(t_byte) * 8);
	while (i > -1)
	{
		if (c & 1)
			byte[i].bit = 1;
		else
			byte[i].bit = 0;
		c >>= 1;
		i--;
	}
	return (byte);
}

void	byte_sender(t_byte *byte, int *pid)
{
	int	i;
	static int count = 1;

	i = 0;
	count++;
	while (i < 8)
	{
		if (!byte[i].bit)
		{
			kill(*pid, SIGUSR1);
			usleep(700);
		}
		else
		{
			kill(*pid, SIGUSR2);
			usleep(700);
		}
		i++;
	}
	free(byte);
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
		{
			kill(server_pid, SIGUSR2);
			usleep(100);
		}
		else
		{
			kill(server_pid, SIGUSR1);
			usleep(100);
		}
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
		ft_printf("Received signal!");
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
		return(ft_printf("Usage: ./client [PID] [STRING]\n"));
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
