/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:04:44 by coder             #+#    #+#             */
/*   Updated: 2022/11/10 16:30:14 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_scpy(char *d, const char *s);
static int	ft_len(const char *str);

char	*ft_strdup(const char *s1)
{
	char	*k;

	k = (char *) malloc(ft_len(s1) + 2);
	if (!k)
		return (NULL);
	if (k != NULL)
		ft_scpy(k, s1);
	return (k);
}

static char	*ft_scpy(char *d, const char *s)
{
	while (*s)
	{
		*d = *s;
		s++;
		d++;
	}
	*d = '\0';
	d++;
	*d = '\0';
	return (d);
}

static int	ft_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
