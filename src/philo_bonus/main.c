/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:12:31 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 14:40:19 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parents(t_table *table, pid_t *pids)
{
	int		i;
	int		status;

	i = -1;
	while (++i < table->nphilo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < table->nphilo)
				kill(pids[i], SIGKILL);
		}
	}
}

static int	philo_childs(t_table *table)
{
	pid_t	*pids;
	int		i;

	i = -1;
	pids = (pid_t *)malloc(table->nphilo * sizeof(pid_t));
	if (!pids)
		return (1);
	gettimeofday(&table->startime, NULL);
	while (++i < table->nphilo)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (1);
		if (pids[i] == 0)
		{
			table->id = i;
			break ;
		}
	}
	if (pids[table->id] == 0)
		philo(table, table->id + 1);
	else
		parents(table, pids);
	free(pids);
	return (0);
}

static int	set_table(t_table *table, char **argv, int argc)
{
	table->startime.tv_sec = 0;
	table->startime.tv_usec = 0;
	table->nphilo = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->id = 0;
	if (table->nphilo <= 0 || table->t_die < 0
		|| table->t_eat < 0 || table->t_sleep < 0)
		return (1);
	if (argc == 6)
		table->ndinner = ft_atoi(argv[5]);
	else
		table->ndinner = 0;
	sem_unlink("sem_fork");
	sem_unlink("sem_death");
	sem_unlink("sem_print");
	table->sem_fork = sem_open("sem_fork",
			O_CREAT | O_EXCL, 0644, table->nphilo);
	table->sem_death = sem_open("sem_death",
			O_CREAT | O_EXCL, 0644, 1);
	table->sem_print = sem_open("sem_print",
			O_CREAT | O_EXCL, 0644, 1);
	return (0);
}

static int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (-1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc > 4 && argc <= 6)
	{
		if (set_table(&table, argv, argc))
			return (ft_error("The table is not set\n"));
		if (philo_childs(&table))
			return (ft_error("Parents does not fork the philosophers\n"));
		sem_close(table.sem_fork);
		sem_close(table.sem_death);
		return (0);
	}
	else
		return (ft_error("Error: Arguments not 5 or 6\n"));
}
