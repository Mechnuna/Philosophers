/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:17:09 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 11:54:02 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_threads(t_threads *table, t_forks **forks)
{
	t_p	philo;
	int	i;

	philo.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	table->write = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo.mutex && !table->write)
		return (1);
	pthread_mutex_init(philo.mutex, NULL);
	pthread_mutex_init(table->write, NULL);
	i = -1;
	while (++i < table->philo_num)
	{
		pthread_mutex_lock(philo.mutex);
		philo.table = table;
		philo.forks = *forks;
		init_p(&philo, i);
		if (pthread_create(&table->thread[i], NULL, &philos, &philo) != 0)
			return (1);
	}
	gettimeofday(&table->star_time, NULL);
	i = -1;
	while (++i < table->philo_num)
		pthread_join(table->thread[i], NULL);
	free_all(table, philo);
	return (0);
}

static int	set_forks(t_threads *table, t_forks **forks)
{
	int	i;

	table->thread = (pthread_t *)malloc(table->philo_num * sizeof(pthread_t));
	*forks = (t_forks *)malloc(table->philo_num * sizeof(t_forks));
	if (!table->thread || !forks)
		return (1);
	i = -1;
	while (++i < table->philo_num)
	{
		(*forks + i)->fork = 1;
		if (pthread_mutex_init(&(*forks + i)->mutex, NULL))
			return (1);
	}
	return (0);
}

int	parse(int argc, char **argv, t_threads *threads, t_forks **forks)
{
	if (argc == 5 || argc == 6)
	{
		threads->star_time.tv_sec = 0;
		threads->star_time.tv_usec = 0;
		threads->number_of_time_to_eat = 0;
		if (argc == 6)
			threads->number_of_time_to_eat = ft_atoi(argv[5]);
		threads->philo_num = ft_atoi(argv[1]);
		threads->time_to_die = ft_atoi(argv[2]);
		threads->time_to_eat = ft_atoi(argv[3]);
		threads->time_to_sleep = ft_atoi(argv[4]);
		threads->death = 0;
		threads->deadlock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!threads->deadlock)
			return (0);
		pthread_mutex_init(threads->deadlock, NULL);
		if (set_forks(threads, forks))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	check_parse(t_threads *threads, int argc, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(is_all_digit(argv[i])))
			return (1);
		i++;
	}
	return (threads->philo_num < 1 || threads->time_to_die <= 0
		|| threads->time_to_eat <= 0 || threads->time_to_sleep <= 0
		|| (argc == 6 && threads->number_of_time_to_eat <= 0));
}

int	main(int argc, char **argv)
{
	t_threads	threads;
	t_forks		*forks;

	if (argc > 4 && argc <= 6)
	{
		if (!(parse(argc, argv, &threads, &forks)))
			return (ft_error("Error: Not valid args!\n"));
		if (check_parse(&threads, argc, argv))
			return (ft_error("Error: Wrong argunets\n"));
		if (philo_threads(&threads, &forks))
			return (ft_error("Error: Wrong argunets\n"));
		free_mem(&threads, forks);
		return (0);
	}
	else
		return (ft_error("Error: Arguments not 5 or 6\n"));
}
