/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:19:45 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 12:26:48 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philos_routine(t_p *philo)
{
	if (philo->group == 2)
		my_uslip(philo->table->time_to_eat);
	if (philo->group == 3)
		my_uslip(philo->table->time_to_eat * 2);
	while (!any_dead(philo))
	{
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (philo->table->number_of_time_to_eat
			&& (philo->eat == philo->table->number_of_time_to_eat))
		{
			philo->iamfull = 1;
			break ;
		}
		if (thinking(philo))
			break ;
	}
}

static int	group(t_p *philo)
{
	int	group;

	if (philo->table->philo_num % 2 != 0
		&& philo->id_p == philo->table->philo_num
		&& philo->table->philo_num != 1)
		group = 3;
	else if (philo->id_p % 2 != 0)
		group = 1;
	else
		group = 2;
	return (group);
}

void	*check(void *arg)
{
	t_p	*philo;

	philo = (t_p *)arg;
	while (!(any_dead(philo)))
	{
		if (philo->iamfull)
			break ;
	}
	return (NULL);
}

void	*philos(void *philo)
{
	t_p			me_philo;
	pthread_t	death_t;

	me_philo = *(t_p *)philo;
	pthread_create(&death_t, NULL, check, &me_philo);
	pthread_mutex_unlock(me_philo.mutex);
	me_philo.eat = 0;
	while (!me_philo.table->star_time.tv_sec
		&& !me_philo.table->star_time.tv_usec)
		usleep(SLEEP);
	me_philo.eatime = me_philo.table->star_time;
	me_philo.group = group(&me_philo);
	philos_routine(&me_philo);
	pthread_join(death_t, NULL);
	return (NULL);
}

void	free_all(t_threads *table, t_p philo)
{
	pthread_mutex_destroy(philo.mutex);
	pthread_mutex_destroy(philo.table->write);
	free(philo.mutex);
	free(table->write);
}
