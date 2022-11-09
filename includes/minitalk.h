/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:53:29 by edu               #+#    #+#             */
/*   Updated: 2022/11/09 16:45:12 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libput.h"
# include <signal.h>
# include <unistd.h>
# include <stdio.h>	

typedef struct s_byte {
	unsigned int	bit : 1;
}				t_byte;

typedef struct s_msg {
	t_byte			*byte;
	unsigned char	c;
	int				index;
	int				init;
}				t_msg;

#endif
