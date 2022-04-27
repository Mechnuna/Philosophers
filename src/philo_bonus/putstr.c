/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:12:21 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 14:26:57 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	int		i;

	if (!(s) || !(fd))
		return ;
	i = 0;
	if (*s == '\0')
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}
