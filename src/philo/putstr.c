/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:49:56 by a79856            #+#    #+#             */
/*   Updated: 2022/02/01 03:05:23 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	init_p(t_p	*philo, int i)
{
	philo->id_p = i + 1;
	philo->iamfull = 0;
}

int	ft_write(t_p *philo, char *str, long time)
{
	pthread_mutex_lock(philo->table->write);
	if (!(any_dead(philo)))
	{
		printf("%ld %d %s", time, philo->id_p, str);
		pthread_mutex_unlock(philo->table->write);
		return (1);
	}
	pthread_mutex_unlock(philo->table->write);
	return (0);
}
