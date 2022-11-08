/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:52:31 by edu               #+#    #+#             */
/*   Updated: 2022/11/08 08:16:38 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	send_signals(char *str, int pid)
{
	t_byte	*byte;
	int		i;

	i = 0;
	byte = byte_maker(*str);
	ft_printf("[%d, %d, %d, %d, %d, %d, %d, %d]\n", byte[0].bit, byte[1].bit, byte[2].bit, byte[3].bit, byte[4].bit, byte[5].bit, byte[6].bit, byte[7].bit);
	while (i < 8)
	{
		if (!byte[i].bit)
		{
			kill(pid, SIGUSR1);
			usleep(500);
		}
		else
		{
			kill(pid, SIGUSR2);
			usleep(500);
		}
		i++;
	}
	free(byte);
	ft_printf("PID = %d, STR = %s\n", pid, str);
}

int	main(int argc, char *argv[])
{	
	int	pid;

	if (argc != 3)
		return(ft_printf("Usage: ./client [PID] [STRING]"));
	pid = ft_atoi(argv[1]);
	send_signals(argv[2], pid);
	return (0);
}
