/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:12:53 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 14:26:56 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_table *table)
{
	struct timeval	now;
	long int		period;

	gettimeofday(&now, NULL);
	period = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (table->eatime.tv_sec * 1000 + table->eatime.tv_usec / 1000);
	if (period > table->t_die)
		return (1);
	return (0);
}

void	*philo_dead(void *table)
{
	while (1)
	{
		sem_wait(((t_table *)table)->sem_death);
		if (is_dead((t_table *)table))
		{
			sem_wait(((t_table *)table)->sem_print);
			printf("%ld %d died\n", o_clock((t_table *)table),
				((t_table *)table)->id);
			exit(1);
		}
		sem_post(((t_table *)table)->sem_death);
		usleep(900);
	}
	return (NULL);
}

long int	o_clock(t_table *table)
{
	struct timeval	now;
	long int		ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (table->startime.tv_sec * 1000
			+ table->startime.tv_usec / 1000);
	return (ms);
}

int	my_uslip(t_table *table, int time)
{
	struct timeval	now;
	struct timeval	end;
	int				i;

	(void)table;
	gettimeofday(&now, NULL);
	gettimeofday(&end, NULL);
	i = 0;
	while ((end.tv_sec * 1000 + end.tv_usec / 1000)
		- (now.tv_sec * 1000 + now.tv_usec / 1000) < time)
	{
		usleep(100);
		gettimeofday(&end, NULL);
	}
	return (0);
}
